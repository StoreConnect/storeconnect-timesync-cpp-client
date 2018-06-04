## server date library

Provides remote server date synchronisation for a client app.

### Requirements

- Cmake v3.9 ([https://cmake.org/](https://cmake.org/))
- Google Test ( [https://github.com/google/googletest](https://github.com/google/googletest), commit `4e4df226fc197c0dda6e37f5c8c3845ca1e73a49`)
- EasyHttp v1.0.0 ([https://github.com/sony/easyhttpcpp/wiki/Installing-EasyHttp](https://github.com/sony/easyhttpcpp/wiki/Installing-EasyHttp))

When checking out the project repo remember about git submodules. Pull them by running the following command
in the project's main directory:

```
git submodule update --init --recursive
```

### Testing

To launch unit test of the project one need to run a server that returns a json like:

```
{
	time_now: "2018-06-04T11:19:31.241Z",
	time_now_millis: 1528111171241
}
```

The sample server code in node.js doing this job is attached to this repository inside the `node_server_date` directory. To run the server node.js ([https://nodejs.org/](https://nodejs.org/en/)) must be installed on the machine. After it is installed one has to open the `node_server_date` dir in the terminal and run:

1. `npm install`
2. `node server.js`

Server can be tested in the browser at `http://localhost:3000/time_now`