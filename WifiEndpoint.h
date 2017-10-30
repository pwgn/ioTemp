#ifndef WifiEndpoint_h
#define WifiEndpoint_h

struct WifiEndpoint {
  String name;
  void (*callback)(void);
};

#endif
