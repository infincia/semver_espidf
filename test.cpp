
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <map>
#include <mutex>

#include <sstream>
#include <iostream>
#include <iomanip>

#include <Semver.hpp>

/**
 * Equal
 *
 */

void test_equal() {
    printf("is equal:\t ");
    Semver a("0.0.1");
    Semver b("0.0.1");

    assert(a == b);

    printf("PASSED\n");
}


/**
 * Not equal
 *
 */

void test_not_equal() {
    printf("not equal:\t ");

    Semver a("0.0.1");
    Semver b("0.0.2");

    assert(a != b);
    assert(b != a);

    printf("PASSED\n");
}

/**
 * Greater than
 *
 */

void test_gt() {
    printf("greater than:\t ");

    Semver a("0.0.1");
    Semver b("0.0.2");

    assert(b > a);


    Semver c("0.0.1");
    Semver d("0.1.2");

    assert(d > c);


    Semver e("0.1.1");
    Semver f("1.0.0");

    assert(f > e);

    printf("PASSED\n");
}

/**
 * Less than
 *
 */

void test_lt() {
    printf("less than:\t ");

    Semver a("0.0.1");
    Semver b("0.0.2");

    assert(a < b);

    Semver c("0.0.1");
    Semver d("0.1.2");

    assert(c < d);


    Semver e("0.1.1");
    Semver f("1.0.0");

    assert(e < f);

    printf("PASSED\n");
}

/**
 * Entry point
 *
 */

extern "C" {
int main();
}


int main() {
    printf("\n********\nsemver_espidf tests\n\n********\n\n");
    
    test_equal();
    
    test_not_equal();

    test_gt();

    test_lt();


    return 0;
}
