## server date library

Provides server date.

### Requirements

**NOTE: **
To launch unit test of the project one need to run a server and paste proper URL into `server_date_tests` line 18.
The GET request to the URL should return a json like:

```
{
time_millis: 1528095138870
}
```


- Cmake v3.9 ([https://cmake.org/](https://cmake.org/))
- Google Test ( [https://github.com/google/googletest](https://github.com/google/googletest), commit `4e4df226fc197c0dda6e37f5c8c3845ca1e73a49`)
- EasyHttp v1.0.0 ([https://github.com/sony/easyhttpcpp/wiki/Installing-EasyHttp](https://github.com/sony/easyhttpcpp/wiki/Installing-EasyHttp))

When checking out the project repo remember about git submodules. Pull them by running the following command
in the project's main directory:

```
git submodule update --init --recursive
```