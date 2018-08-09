# Flog

![language](https://img.shields.io/badge/language-c++-blue.svg)
![c++](https://img.shields.io/badge/std-c%2B%2B11-blue.svg)
![GCC](https://img.shields.io/badge/GCC-5.4.0-blue.svg)
![GCC](https://img.shields.io/badge/GCC-4.9.3-blue.svg)
![GCC](https://img.shields.io/badge/GCC-4.8.5-blue.svg)
![license](https://img.shields.io/badge/license-GPLv3-blue.svg)

A very simple and fast c++ logging library. Current backend is cerr. Removing
mysql backend for simplicity. (I will add more backends using callback functions
which is more flexible).

## Usage

```c++
using namespace flog;
auto l = logger::instance();
l->log("Checking engines...");
l->log(logger::level::INFO, "Inspection procedure started, please standby...");
l->log(logger::level::TRACE, "We are here at %d with %s", line, "Coder");
l->log(logger::level::DEBUG, "Entered engine check function...");
for(int engine=1; engine <= engine_count; ++engine)
{
    std::this_thread::sleep_for(std::chrono::seconds{5});
    l->log(logger::level::ERROR_,"Engine %d down!", engine);
}
l->log(logger::level::FATAL,"We will die on this planet...");
```

Which will possibly output:

```
[2017-09-10 11:36:44.452][ INFO]: Checking engines...
[2017-09-10 11:36:44.452][ INFO]: Inspection procedure started, please standby...
[2017-09-10 11:36:44.452][TRACE]: We are here at 16582 with Coder
[2017-09-10 11:36:44.452][DEBUG]: Entered engine check function...
[2017-09-10 11:36:48.001][ERROR]: Engine 1 down!
[2017-09-10 11:36:54.191][ERROR]: Engine 2 down!
[2017-09-10 11:36:59.452][ERROR]: Engine 3 down!
[2017-09-10 11:37:04.463][ERROR]: Engine 4 down!
[2017-09-10 11:37:04.353][FATAL]: We will die on this planet...
```
