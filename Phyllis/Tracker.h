#if defined(DEBUG) || defined(_DEBUG)
struct MEM_REF;

void tracker_Track(LPVOID s, UINT l, char * f);
void tracker_Untrack(LPVOID lpv);
void tracker_Cleanup();

#define xtrack(s) tracker_Track(s, __LINE__, __FILE__)
#define xuntrack(s) tracker_Untrack(s)
#define xcleanup() tracker_Cleanup()

#else

#define xtrack(s) void()
#define xuntrack(s) void()
#define xcleanup() void()

#endif
