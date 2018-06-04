## server date library Android wrapper

Provides remote server date synchronisation for a mobile app

### Requirements to build the project

Android SDK Tools (should be installed via [Android SDK Manager](https://developer.android.com/studio/intro/update)):

- Android NDK (r17)
- CMake (min version 3.4.1)

Global components:

- [SWIG](http://www.swig.org/): an interface compiler for generating Java classes that are interfaces to C++ classes

### How to use

The sample app attached to this project presents a usage of the library. Please note that a valid IP address has to be entered into the constructor:

```
val mServerDate = ServerDate("http://192.168.2.242:3000/time_now", applicationContext)
mServerDate.start()
```