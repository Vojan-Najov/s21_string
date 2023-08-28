# s21_string+
Implementation of the string.h library with additions: 
sprintf, sscanf and other strings functions.

## Subject

- [Subject EN](./docs/subject_en.md)
- [Subject RU](./docs/subject_ru.md)

## Solution

`$> make s21_string.a` to build library.

`$> make test && ./test` to run unit tests using libcheck.

`$> sh tests/scripts/run.sh` to run docker container with tests.

`$> make gcov_report` to build coverage report `gcov_report/index.html`.
