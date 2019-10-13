# TraceLog

Template based system log trace library with examples for Screen, File and Tcp logs

### Compiling

C++ compatible compiler and make is required.

```sh
$ make clean
$ make
```
### Running


Trace Log to Screen:
```sh
$ ./screenlog
```

Trace Log to File:
```sh
$ ./filelog
```

Trace Log to Tcp:
- Run listener server
```sh
$ ./tcplistener <port>
```
- Run trace log test:
```sh
$ ./tcplog <port>
```
