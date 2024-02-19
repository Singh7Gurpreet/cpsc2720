# Revision History -- at the bottom of the document
################################################################################
# The targets in this file are used in .gitlab-ci.yml and  the files created
# are found in the .gitignore
################################################################################
# Changing any names below can change the target names which will require that
# you update .gitlab_ci.yml and .gitignore
################################################################################

################################################################################
# Variable definitions
################################################################################

# Executable names
PROJECT = bingo
GTEST = test_${PROJECT}

# Compilation command and flags
CXX=g++
CXXVERSION= -std=c++14
CXXFLAGS= ${CXXVERSION} -g
CXXWITHCOVERAGEFLAGS = ${CXXFLAGS} -fprofile-arcs -ftest-coverage
LINKFLAGS= -lgtest

# Directories
SRC_DIR = src
PROJECT_SRC_DIR = src/project
GTEST_DIR = test
TEST_OUTPUT = ${GTEST_DIR}/output
SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

# Output Files
CARD = bingoCardTest
VALID = validityDisplayTest
INSTRUCTIONS = bingoInstructions

# Tool variables
GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = docs/coverage/results.coverage
COVERAGE_DIR = docs/coverage/results
STATIC_ANALYSIS = cppcheck
STYLE_CHECK = cpplint
DESIGN_DIR = docs/design
DOXY_DIR = docs/code

################################################################################
# Targets
################################################################################

# Default goal
.DEFAULT_GOAL := bingo

################################################################################
# Clean-up targets
################################################################################

.PHONY: clean-cov
clean-cov:
	rm -rf *.gcov *.gcda *.gcno ${COVERAGE_RESULTS} ${COVERAGE_DIR}

.PHONY: clean-docs
clean-docs:
	rm -rf docs/code/src/

.PHONY: clean-exec
clean-exec:
	rm -rf ${PROJECT} ${GTEST} ${PROJECT}.exe ${GTEST}.exe \
	${TEST_OUTPUT}/*.actual

.PHONY: clean-obj
clean-obj:
	rm -rf ${SRC}/*.o

.PHONY: clean-temp
clean-temp:
	rm -rf *~ \#* .\#* \
	${SRC_DIR}/*~ ${SRC_DIR}/\#* ${SRC_DIR}/.\#* \
	${GTEST_DIR}/*~ ${GTEST_DIR}/\#* ${GTEST_DIR}/.\#* \
	${SRC_INCLUDE}/*~ ${SRC_INCLUDE}/\#* ${SRC_INCLUDE}/.\#* \
	${PROJECT_SRC_DIR}/*~ ${PROJECT_SRC_DIR}/\#* ${PROJECT_SRC_DIR}/.\#* \
	${DESIGN_DIR}/*~ ${DESIGN_DIR}/\#* ${DESIGN_DIR}/.\#* \
	*.gcov *.gcda *.gcno 

.PHONY: clean
clean: clean-cov clean-docs clean-exec clean-obj clean-temp

################################################################################
# Compilaton targets
################################################################################

# default rule for compiling .cpp to .o
%.o: %.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

# Compilation targets

# compilation for performing testing
# using the files in include, src, and test, but not src/project
${GTEST}: ${GTEST_DIR} ${SRC_DIR} clean-exec
	${CXX} ${CXXVERSION} -o ./${GTEST} ${INCLUDE} \
	${GTEST_DIR}/*.o ${SRC_DIR}/*.cpp ${LINKFLAGS}

# compilation for performing testing
# using the files in include, src, and test, but not src/project
# with the debug flag.
${GTEST}_g: ${GTEST_DIR} ${SRC_DIR} clean-exec
	${CXX} ${CXXFLAGS} -o ./${GTEST} ${INCLUDE} \
	${GTEST_DIR}/*.o ${SRC_DIR}/*.cpp ${LINKFLAGS}

# compilation for making the project
# using the files in include, src, and src/project, but not test
${PROJECT}: ${SRC_DIR} ${PROJECT_SRC_DIR} clean-exec
	${CXX} ${CXXVERSION} -o ${PROJECT} ${INCLUDE} \
	${SRC_DIR}/*.cpp ${PROJECT_SRC_DIR}/*.cpp

# compilation for making the project
# using the files in include, src, and src/project, but not test
# with the debug flag
${project}_g: ${SRC_DIR} ${PROJECT_SRC_DIR} clean-exec
	${CXX} ${CXXFLAGS} -o ${PROJECT} ${INCLUDE} \
	${SRC_DIR}/*.cpp ${PROJECT_SRC_DIR}/*.cpp

################################################################################
# Test targets
################################################################################

# To perform all tests
all: ${GTEST} diffs memcheck coverage docs static style

# To compare actual and expected output
.PHONY: test_output_diff 
diffs: ${GTEST}
	./${GTEST}
	diff -s ${TEST_OUTPUT}/${CARD}.actual ${TEST_OUTPUT}/${CARD}.expected
	diff -s ${TEST_OUTPUT}/${VALID}.actual ${TEST_OUTPUT}/${VALID}.expected
	diff -s ${TEST_OUTPUT}/${INSTRUCTIONS}.actual ${TEST_OUTPUT}/${INSTRUCTIONS}.expected

# To perform the memory checks
memcheck: ${GTEST}
	valgrind --tool=memcheck --leak-check=yes --error-exitcode=1 ./${GTEST}

fullmemcheck: ${GTEST}
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./${GTEST}



# To perform the code coverage checks
coverage: clean-exec clean-cov
	${CXX} ${CXXWITHCOVERAGEFLAGS} -o ./${GTEST} ${INCLUDE} \
	${GTEST_DIR}/*.o ${SRC_DIR}/*.cpp ${LINKFLAGS}
	./${GTEST}
	# Determine code coverage
	${LCOV} --capture --gcov-tool ${GCOV} --directory . --output-file \
	${COVERAGE_RESULTS} --rc lcov_branch_coverage=1
	# Only show code coverage for the source code files (not library files)
	${LCOV} --extract ${COVERAGE_RESULTS} */*/*/${SRC_DIR}/* -o \
	${COVERAGE_RESULTS}
	#Generate the HTML reports
	genhtml ${COVERAGE_RESULTS} --output-directory ${COVERAGE_DIR}
	#Remove all of the generated files from gcov
	make clean-temp

# To perform the static check 
static: ${SRC_DIR} ${GTEST_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR} ${GTEST_DIR} \
	${SRC_INCLUDE} --suppress=missingInclude --error-exitcode=1

# To perform the style check
style: ${SRC_DIR} ${SRC_INCLUDE}
	${STYLE_CHECK} ${SRC_DIR}/* ${SRC_INCLUDE}/*	

################################################################################
# Documentation target
################################################################################

# To produce the documentation
.PHONY: docs
docs: ${SRC_INCLUDE}
	doxygen ${DOXY_DIR}/doxyfile

################################################################################
# Revision History
################################################################################
# Updated: 2023-10-19 Nicole Wilson <n.wilson@uleth.ca>
#  Updated and added compilation targets so that compilation normally doesn't
# use -g (debug - includes source code) but targets that do use it are available.
################################################################################
# Updated: 2022-12-15 Nicole Wilson <n.wilson@uleth.ca>
#  Removed all references to OS as the pipelines are now running on Ubuntu
################################################################################
# Updated: 2022-10-19 Dr. J. Anvik <john.anvik@uleth.ca>
#  Changed the static command to make the pipeline fail on exit with errors.
################################################################################
# Updated: 2022-09-11 Nicole Wilson <n.wilson@uleth.ca>
#  Added reference to OS in setting of STYLE_CHECK.
#  This is a temporary measure until the pipelines are running on Ubuntu
################################################################################
