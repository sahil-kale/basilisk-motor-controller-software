MAKEFILE_DIR=$(dir $(realpath $(firstword $(MAKEFILE_LIST))))
PROJECT_DIR=$(realpath $(MAKEFILE_DIR)..)
TEST_DIR=$(PROJECT_DIR)/test

CPPUTEST_HOME=$(PROJECT_DIR)/../cpputest

# project source files path
SRC_DIRS=$(PROJECT_DIR)/src

# project header files path
INCLUDE_DIRS=$(PROJECT_DIR)/inc

# add this to avoid problems when including cpputest headers on test files
INCLUDE_DIRS+=$(CPPUTEST_HOME)/include

## specify where the test code is located
TEST_SRC_DIRS=$(TEST_DIR)

## mock path
MOCKS_SRC_DIRS=$(TEST_DIR)/mocks

## what to call the test binary
TEST_TARGET=test_runner

CPPUTEST_CPPFLAGS+=-Wno-error=unused-parameter
CPPUTEST_CPPFLAGS+=-Wno-error=unused-variable

# Add the library linking to use Cppumock
LD_LIBRARIES += -L$(CPPUTEST_HOME)/lib -lCppUTestExt


#run MakefileWorker.mk with the variables defined here
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

# GODLY TUTORIAL SOURCE:
# https://matheusmbar.com/bugfree-robot/2019/04/05/makefile-first-test.html
