/*  Ofront 1.2 -spke */
#include "SYSTEM.h"

typedef
	CHAR (*Platform_ADR)[1];

typedef
	CHAR (*Platform_ArgPtr)[1024];

typedef
	Platform_ArgPtr (*Platform_ArgVec)[1024];

typedef
	struct Platform_FileIdentity {
		LONGINT volume, indexhigh, indexlow, mtimehigh, mtimelow;
	} Platform_FileIdentity;

typedef
	void (*Platform_HaltProcedure)(LONGINT);

typedef
	void (*Platform_SignalHandler)(INTEGER);


export BOOLEAN Platform_LittleEndian;
export Platform_ADR Platform_MainStackFrame;
export LONGINT Platform_HaltCode;
export INTEGER Platform_PID;
export CHAR Platform_CWD[4096];
export INTEGER Platform_ArgCount;
export Platform_ArgVec Platform_ArgVector;
static Platform_HaltProcedure Platform_HaltHandler;
static LONGINT Platform_TimeStart;
export INTEGER Platform_SeekSet, Platform_SeekCur, Platform_SeekEnd;
export LONGINT Platform_StdIn, Platform_StdOut, Platform_StdErr;
static Platform_SignalHandler Platform_InterruptHandler;
export CHAR Platform_nl[3];

export LONGINT *Platform_FileIdentity__typ;

export BOOLEAN Platform_Absent (INTEGER e);
export INTEGER Platform_ArgPos (CHAR *s, LONGINT s__len);
export void Platform_AssertFail (LONGINT code);
export INTEGER Platform_Chdir (CHAR *n, LONGINT n__len);
export INTEGER Platform_Close (LONGINT h);
export BOOLEAN Platform_ConnectionFailed (INTEGER e);
export void Platform_Delay (LONGINT ms);
export BOOLEAN Platform_DifferentFilesystems (INTEGER e);
static void Platform_DisplayHaltCode (LONGINT code);
export INTEGER Platform_Error (void);
export void Platform_Exit (INTEGER code);
export void Platform_GetArg (INTEGER n, CHAR *val, LONGINT val__len);
export void Platform_GetClock (LONGINT *t, LONGINT *d);
export void Platform_GetEnv (CHAR *var, LONGINT var__len, CHAR *val, LONGINT val__len);
export void Platform_GetIntArg (INTEGER n, INTEGER *val);
export void Platform_GetTimeOfDay (LONGINT *sec, LONGINT *usec);
export void Platform_Halt (LONGINT code);
export INTEGER Platform_Identify (LONGINT h, Platform_FileIdentity *identity, LONGINT *identity__typ);
export INTEGER Platform_IdentifyByName (CHAR *n, LONGINT n__len, Platform_FileIdentity *identity, LONGINT *identity__typ);
export BOOLEAN Platform_Inaccessible (INTEGER e);
export void Platform_Init (INTEGER argc, SYSTEM_PTR argvadr);
export void Platform_MTimeAsClock (Platform_FileIdentity i, LONGINT *t, LONGINT *d);
export INTEGER Platform_New (CHAR *n, LONGINT n__len, LONGINT *h);
export BOOLEAN Platform_NoSuchDirectory (INTEGER e);
export LONGINT Platform_OSAllocate (LONGINT size);
export void Platform_OSFree (LONGINT address);
export INTEGER Platform_OldRO (CHAR *n, LONGINT n__len, LONGINT *h);
export INTEGER Platform_OldRW (CHAR *n, LONGINT n__len, LONGINT *h);
export INTEGER Platform_Read (LONGINT h, LONGINT p, LONGINT l, LONGINT *n);
export INTEGER Platform_ReadBuf (LONGINT h, BYTE *b, LONGINT b__len, LONGINT *n);
export INTEGER Platform_Rename (CHAR *o, LONGINT o__len, CHAR *n, LONGINT n__len);
export BOOLEAN Platform_SameFile (Platform_FileIdentity i1, Platform_FileIdentity i2);
export BOOLEAN Platform_SameFileTime (Platform_FileIdentity i1, Platform_FileIdentity i2);
export INTEGER Platform_Seek (LONGINT h, LONGINT o, INTEGER r);
export void Platform_SetBadInstructionHandler (Platform_SignalHandler handler);
export void Platform_SetHalt (Platform_HaltProcedure p);
export void Platform_SetMTime (Platform_FileIdentity *target, LONGINT *target__typ, Platform_FileIdentity source);
export INTEGER Platform_Size (LONGINT h, LONGINT *l);
export INTEGER Platform_Sync (LONGINT h);
export INTEGER Platform_System (CHAR *cmd, LONGINT cmd__len);
static void Platform_TestLittleEndian (void);
export LONGINT Platform_Time (void);
export BOOLEAN Platform_TimedOut (INTEGER e);
export BOOLEAN Platform_TooManyFiles (INTEGER e);
export INTEGER Platform_Truncate (LONGINT h, LONGINT limit);
export INTEGER Platform_Unlink (CHAR *n, LONGINT n__len);
export INTEGER Platform_Write (LONGINT h, LONGINT p, LONGINT l);
static void Platform_YMDHMStoClock (INTEGER ye, INTEGER mo, INTEGER da, INTEGER ho, INTEGER mi, INTEGER se, LONGINT *t, LONGINT *d);
static void Platform_errch (CHAR c);
static void Platform_errint (LONGINT l);
static void Platform_errln (void);
static void Platform_errposint (LONGINT l);
export BOOLEAN Platform_getEnv (CHAR *var, LONGINT var__len, CHAR *val, LONGINT val__len);

#include "_windows.h"
#define Platform_ECONNABORTED()	WSAECONNABORTED
#define Platform_ECONNREFUSED()	WSAECONNREFUSED
#define Platform_EHOSTUNREACH()	WSAEHOSTUNREACH
#define Platform_ENETUNREACH()	WSAENETUNREACH
#define Platform_ERRORACCESSDENIED()	ERROR_ACCESS_DENIED
#define Platform_ERRORFILENOTFOUND()	ERROR_FILE_NOT_FOUND
#define Platform_ERRORNOTREADY()	ERROR_NOT_READY
#define Platform_ERRORNOTSAMEDEVICE()	ERROR_NOT_SAME_DEVICE
#define Platform_ERRORPATHNOTFOUND()	ERROR_PATH_NOT_FOUND
#define Platform_ERRORSHARINGVIOLATION()	ERROR_SHARING_VIOLATION
#define Platform_ERRORTOOMANYOPENFILES()	ERROR_TOO_MANY_OPEN_FILES
#define Platform_ERRORWRITEPROTECT()	ERROR_WRITE_PROTECT
#define Platform_ETIMEDOUT()	WSAETIMEDOUT
extern void Heap_InitHeap();
#define Platform_GetTickCount()	(LONGINT)(unsigned)GetTickCount()
#define Platform_HeapInitHeap()	Heap_InitHeap()
#define Platform_SetInterruptHandler(h)	SystemSetInterruptHandler((SYSTEM_ADR)h)
#define Platform_SetQuitHandler(h)	SystemSetQuitHandler((SYSTEM_ADR)h)
#define Platform_allocate(size)	(LONGINT)(SYSTEM_ADR)((void*)HeapAlloc(GetProcessHeap(), 0, (size_t)size))
#define Platform_bhfiIndexHigh()	(LONGINT)bhfi.nFileIndexHigh
#define Platform_bhfiIndexLow()	(LONGINT)bhfi.nFileIndexLow
#define Platform_bhfiMtimeHigh()	(LONGINT)bhfi.ftLastWriteTime.dwHighDateTime
#define Platform_bhfiMtimeLow()	(LONGINT)bhfi.ftLastWriteTime.dwLowDateTime
#define Platform_bhfiVsn()	(LONGINT)bhfi.dwVolumeSerialNumber
#define Platform_byHandleFileInformation()	BY_HANDLE_FILE_INFORMATION bhfi
#define Platform_cleanupProcess()	CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
#define Platform_closeHandle(h)	(INTEGER)CloseHandle((HANDLE)(SYSTEM_ADR)h)
#define Platform_createProcess(str, str__len)	(INTEGER)CreateProcess(0, (char*)str, 0,0,0,0,0,0,&si,&pi)
#define Platform_deleteFile(n, n__len)	(INTEGER)DeleteFile((char*)n)
#define Platform_err()	(INTEGER)GetLastError()
#define Platform_errc(c)	WriteFile((HANDLE)(SYSTEM_ADR)Platform_StdOut, &c, 1, 0,0)
#define Platform_errstring(s, s__len)	WriteFile((HANDLE)(SYSTEM_ADR)Platform_StdOut, s, s__len-1, 0,0)
#define Platform_exit(code)	ExitProcess((UINT)code)
#define Platform_fileTimeToSysTime()	SYSTEMTIME st; FileTimeToSystemTime(&ft, &st)
#define Platform_flushFileBuffers(h)	(INTEGER)FlushFileBuffers((HANDLE)(SYSTEM_ADR)h)
#define Platform_free(address)	HeapFree(GetProcessHeap(), 0, (void*)(SYSTEM_ADR)address)
#define Platform_getCurrentDirectory(n, n__len)	GetCurrentDirectory(n__len, (char*)n)
#define Platform_getExitCodeProcess(exitcode)	GetExitCodeProcess(pi.hProcess, (DWORD*)exitcode);
#define Platform_getFileInformationByHandle(h)	(INTEGER)GetFileInformationByHandle((HANDLE)(SYSTEM_ADR)h, &bhfi)
#define Platform_getFilePos(h, r, rc)	LARGE_INTEGER liz = {0}; *rc = (INTEGER)SetFilePointerEx((HANDLE)(SYSTEM_ADR)h, liz, &li, FILE_CURRENT); *r = (LONGINT)li.QuadPart
#define Platform_getFileSize(h)	(INTEGER)GetFileSizeEx((HANDLE)(SYSTEM_ADR)h, &li)
#define Platform_getLocalTime()	SYSTEMTIME st; GetLocalTime(&st)
#define Platform_getenv(name, name__len, buf, buf__len)	(INTEGER)GetEnvironmentVariable((char*)name, (char*)buf, buf__len)
#define Platform_getpid()	(INTEGER)GetCurrentProcessId()
#define Platform_getstderrhandle()	(SYSTEM_ADR)GetStdHandle(STD_ERROR_HANDLE)
#define Platform_getstdinhandle()	(SYSTEM_ADR)GetStdHandle(STD_INPUT_HANDLE)
#define Platform_getstdouthandle()	(SYSTEM_ADR)GetStdHandle(STD_OUTPUT_HANDLE)
#define Platform_identityToFileTime(i)	FILETIME ft; ft.dwHighDateTime = i.mtimehigh; ft.dwLowDateTime = i.mtimelow
#define Platform_invalidHandleValue()	((LONGINT)(SYSTEM_ADR)INVALID_HANDLE_VALUE)
#define Platform_largeInteger()	LARGE_INTEGER li
#define Platform_liLongint()	(LONGINT)li.QuadPart
#define Platform_moveFile(o, o__len, n, n__len)	(INTEGER)MoveFileEx((char*)o, (char*)n, MOVEFILE_REPLACE_EXISTING)
#define Platform_opennew(n, n__len)	(LONGINT)(SYSTEM_ADR)CreateFile((char*)n, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0)
#define Platform_openro(n, n__len)	(LONGINT)(SYSTEM_ADR)CreateFile((char*)n, GENERIC_READ              , FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0)
#define Platform_openrw(n, n__len)	(LONGINT)(SYSTEM_ADR)CreateFile((char*)n, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0)
#define Platform_processInfo()	PROCESS_INFORMATION pi = {0};
#define Platform_readfile(fd, p, l, n)	(INTEGER)ReadFile ((HANDLE)(SYSTEM_ADR)fd, (void*)(SYSTEM_ADR)(p), (DWORD)l, (DWORD*)n, 0)
#define Platform_seekcur()	FILE_CURRENT
#define Platform_seekend()	FILE_END
#define Platform_seekset()	FILE_BEGIN
#define Platform_setCurrentDirectory(n, n__len)	(INTEGER)SetCurrentDirectory((char*)n)
#define Platform_setEndOfFile(h)	(INTEGER)SetEndOfFile((HANDLE)(SYSTEM_ADR)h)
#define Platform_setFilePointerEx(h, o, r, rc)	li.QuadPart=o; *rc = (INTEGER)SetFilePointerEx((HANDLE)(SYSTEM_ADR)h, li, 0, (DWORD)r)
#define Platform_sleep(ms)	Sleep((DWORD)ms)
#define Platform_startupInfo()	STARTUPINFO si = {0}; si.cb = sizeof(si);
#define Platform_sthour()	(INTEGER)st.wHour
#define Platform_stmday()	(INTEGER)st.wDay
#define Platform_stmin()	(INTEGER)st.wMinute
#define Platform_stmon()	(INTEGER)st.wMonth
#define Platform_stmsec()	(INTEGER)st.wMilliseconds
#define Platform_stsec()	(INTEGER)st.wSecond
#define Platform_styear()	(INTEGER)st.wYear
#define Platform_waitForProcess()	(INTEGER)WaitForSingleObject(pi.hProcess, INFINITE)
#define Platform_writefile(fd, p, l)	(INTEGER)WriteFile((HANDLE)(SYSTEM_ADR)fd, (void*)(SYSTEM_ADR)(p), (DWORD)l, 0,0)

/*============================================================================*/

BOOLEAN Platform_TooManyFiles (INTEGER e)
{
	return e == Platform_ERRORTOOMANYOPENFILES();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_NoSuchDirectory (INTEGER e)
{
	return e == Platform_ERRORPATHNOTFOUND();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_DifferentFilesystems (INTEGER e)
{
	return e == Platform_ERRORNOTSAMEDEVICE();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_Inaccessible (INTEGER e)
{
	return ((e == Platform_ERRORACCESSDENIED() || e == Platform_ERRORWRITEPROTECT()) || e == Platform_ERRORNOTREADY()) || e == Platform_ERRORSHARINGVIOLATION();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_Absent (INTEGER e)
{
	return e == Platform_ERRORFILENOTFOUND() || e == Platform_ERRORPATHNOTFOUND();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_TimedOut (INTEGER e)
{
	return e == Platform_ETIMEDOUT();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_ConnectionFailed (INTEGER e)
{
	return ((e == Platform_ECONNREFUSED() || e == Platform_ECONNABORTED()) || e == Platform_ENETUNREACH()) || e == Platform_EHOSTUNREACH();
}

/*----------------------------------------------------------------------------*/
LONGINT Platform_OSAllocate (LONGINT size)
{
	return Platform_allocate(size);
}

/*----------------------------------------------------------------------------*/
void Platform_OSFree (LONGINT address)
{
	Platform_free(address);
}

/*----------------------------------------------------------------------------*/
typedef
	Platform_ArgVec (*ArgVecPtr__39)[1];

void Platform_Init (INTEGER argc, SYSTEM_PTR argvadr)
{
	ArgVecPtr__39 av = NIL;
	Platform_MainStackFrame = (Platform_ADR)argvadr;
	Platform_ArgCount = argc;
	av = (ArgVecPtr__39)argvadr;
	Platform_ArgVector = (Platform_ArgVec)(*av)[0];
	Platform_HaltCode = -128;
	Platform_HeapInitHeap();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_getEnv (CHAR *var, LONGINT var__len, CHAR *val, LONGINT val__len)
{
	CHAR buf[4096];
	INTEGER res;
	__DUP(var, var__len, CHAR);
	res = Platform_getenv(var, var__len, (void*)buf, 4096);
	if (res > 0 && res < 4096) {
		__COPY(buf, val, val__len);
		__DEL(var);
		return 1;
	} else {
		__DEL(var);
		return 0;
	}
	__RETCHK;
}

/*----------------------------------------------------------------------------*/
void Platform_GetEnv (CHAR *var, LONGINT var__len, CHAR *val, LONGINT val__len)
{
	__DUP(var, var__len, CHAR);
	if (!Platform_getEnv(var, var__len, (void*)val, val__len)) {
		val[0] = 0x00;
	}
	__DEL(var);
}

/*----------------------------------------------------------------------------*/
void Platform_GetArg (INTEGER n, CHAR *val, LONGINT val__len)
{
	if (n < Platform_ArgCount) {
		__COPY(*(*Platform_ArgVector)[n], val, val__len);
	}
}

/*----------------------------------------------------------------------------*/
void Platform_GetIntArg (INTEGER n, INTEGER *val)
{
	CHAR s[64];
	INTEGER k, d, i;
	s[0] = 0x00;
	Platform_GetArg(n, (void*)s, 64);
	i = 0;
	if (s[0] == '-') {
		i = 1;
	}
	k = 0;
	d = (INTEGER)s[i] - 48;
	while (d >= 0 && d <= 9) {
		k = k * 10 + d;
		i += 1;
		d = (INTEGER)s[i] - 48;
	}
	if (s[0] == '-') {
		k = -k;
		i -= 1;
	}
	if (i > 0) {
		*val = k;
	}
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_ArgPos (CHAR *s, LONGINT s__len)
{
	INTEGER i;
	CHAR arg[256];
	__DUP(s, s__len, CHAR);
	i = 0;
	Platform_GetArg(i, (void*)arg, 256);
	while (i < Platform_ArgCount && __STRCMP(s, arg) != 0) {
		i += 1;
		Platform_GetArg(i, (void*)arg, 256);
	}
	__DEL(s);
	return i;
}

/*----------------------------------------------------------------------------*/
void Platform_SetBadInstructionHandler (Platform_SignalHandler handler)
{
}

/*----------------------------------------------------------------------------*/
static void Platform_YMDHMStoClock (INTEGER ye, INTEGER mo, INTEGER da, INTEGER ho, INTEGER mi, INTEGER se, LONGINT *t, LONGINT *d)
{
	*d = (__ASHL((INTEGER)__MOD(ye, 100), 9, INTEGER) + __ASHL(mo + 1, 5, INTEGER)) + da;
	*t = (__ASHL(ho, 12, INTEGER) + __ASHL(mi, 6, INTEGER)) + se;
}

void Platform_GetClock (LONGINT *t, LONGINT *d)
{
	Platform_getLocalTime();
	Platform_YMDHMStoClock(Platform_styear(), Platform_stmon(), Platform_stmday(), Platform_sthour(), Platform_stmin(), Platform_stsec(), &*t, &*d);
}

/*----------------------------------------------------------------------------*/
void Platform_GetTimeOfDay (LONGINT *sec, LONGINT *usec)
{
	Platform_getLocalTime();
	*sec = Platform_stsec();
	*usec = (LONGINT)Platform_stmsec() * 1000;
}

/*----------------------------------------------------------------------------*/
LONGINT Platform_Time (void)
{
	LONGINT ms;
	ms = Platform_GetTickCount();
	return __MOD(ms - Platform_TimeStart, 2147483647);
}

/*----------------------------------------------------------------------------*/
void Platform_Delay (LONGINT ms)
{
	while (ms > 30000) {
		Platform_sleep(30000);
		ms = ms - 30000;
	}
	if (ms > 0) {
		Platform_sleep(ms);
	}
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_System (CHAR *cmd, LONGINT cmd__len)
{
	INTEGER result;
	__DUP(cmd, cmd__len, CHAR);
	result = 127;
	Platform_startupInfo();
	Platform_processInfo();
	if (Platform_createProcess(cmd, cmd__len) != 0) {
		if (Platform_waitForProcess() == 0) {
			Platform_getExitCodeProcess(&result);
		}
		Platform_cleanupProcess();
	}
	__DEL(cmd);
	return __ASHL(result, 8, INTEGER);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Error (void)
{
	return Platform_err();
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_OldRO (CHAR *n, LONGINT n__len, LONGINT *h)
{
	LONGINT fd;
	fd = Platform_openro(n, n__len);
	if (fd == Platform_invalidHandleValue()) {
		return Platform_err();
	} else {
		*h = fd;
		return 0;
	}
	__RETCHK;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_OldRW (CHAR *n, LONGINT n__len, LONGINT *h)
{
	LONGINT fd;
	fd = Platform_openrw(n, n__len);
	if (fd == Platform_invalidHandleValue()) {
		return Platform_err();
	} else {
		*h = fd;
		return 0;
	}
	__RETCHK;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_New (CHAR *n, LONGINT n__len, LONGINT *h)
{
	LONGINT fd;
	fd = Platform_opennew(n, n__len);
	if (fd == Platform_invalidHandleValue()) {
		return Platform_err();
	} else {
		*h = fd;
		return 0;
	}
	__RETCHK;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Close (LONGINT h)
{
	if (Platform_closeHandle(h) == 0) {
		return Platform_err();
	} else {
		return 0;
	}
	__RETCHK;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Identify (LONGINT h, Platform_FileIdentity *identity, LONGINT *identity__typ)
{
	Platform_byHandleFileInformation();
	if (Platform_getFileInformationByHandle(h) == 0) {
		return Platform_err();
	}
	(*identity).volume = Platform_bhfiVsn();
	(*identity).indexhigh = Platform_bhfiIndexHigh();
	(*identity).indexlow = Platform_bhfiIndexLow();
	(*identity).mtimehigh = Platform_bhfiMtimeHigh();
	(*identity).mtimelow = Platform_bhfiMtimeLow();
	return 0;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_IdentifyByName (CHAR *n, LONGINT n__len, Platform_FileIdentity *identity, LONGINT *identity__typ)
{
	LONGINT h;
	INTEGER e, i;
	__DUP(n, n__len, CHAR);
	e = Platform_OldRO((void*)n, n__len, &h);
	if (e != 0) {
		__DEL(n);
		return e;
	}
	e = Platform_Identify(h, &*identity, identity__typ);
	i = Platform_Close(h);
	__DEL(n);
	return e;
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_SameFile (Platform_FileIdentity i1, Platform_FileIdentity i2)
{
	return (i1.indexhigh == i2.indexhigh && i1.indexlow == i2.indexlow) && i1.volume == i2.volume;
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_SameFileTime (Platform_FileIdentity i1, Platform_FileIdentity i2)
{
	return i1.mtimehigh == i2.mtimehigh && i1.mtimelow == i2.mtimelow;
}

/*----------------------------------------------------------------------------*/
void Platform_SetMTime (Platform_FileIdentity *target, LONGINT *target__typ, Platform_FileIdentity source)
{
	(*target).mtimehigh = source.mtimehigh;
	(*target).mtimelow = source.mtimelow;
}

/*----------------------------------------------------------------------------*/
void Platform_MTimeAsClock (Platform_FileIdentity i, LONGINT *t, LONGINT *d)
{
	Platform_identityToFileTime(i);
	Platform_fileTimeToSysTime();
	Platform_YMDHMStoClock(Platform_styear(), Platform_stmon(), Platform_stmday(), Platform_sthour(), Platform_stmin(), Platform_stsec(), &*t, &*d);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Size (LONGINT h, LONGINT *l)
{
	Platform_largeInteger();
	if (Platform_getFileSize(h) == 0) {
		return Platform_err();
	}
	*l = Platform_liLongint();
	return 0;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Read (LONGINT h, LONGINT p, LONGINT l, LONGINT *n)
{
	INTEGER result;
	*n = 0;
	result = Platform_readfile(h, p, l, &*n);
	if (result == 0) {
		*n = 0;
		return Platform_err();
	} else {
		return 0;
	}
	__RETCHK;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_ReadBuf (LONGINT h, BYTE *b, LONGINT b__len, LONGINT *n)
{
	INTEGER result;
	*n = 0;
	result = Platform_readfile(h, (LONGINT)b, b__len, &*n);
	if (result == 0) {
		*n = 0;
		return Platform_err();
	} else {
		return 0;
	}
	__RETCHK;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Write (LONGINT h, LONGINT p, LONGINT l)
{
	if (Platform_writefile(h, p, l) == 0) {
		return Platform_err();
	} else {
		return 0;
	}
	__RETCHK;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Sync (LONGINT h)
{
	if (Platform_flushFileBuffers(h) == 0) {
		return Platform_err();
	} else {
		return 0;
	}
	__RETCHK;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Seek (LONGINT h, LONGINT o, INTEGER r)
{
	INTEGER rc;
	Platform_largeInteger();
	Platform_setFilePointerEx(h, o, r, &rc);
	if (rc == 0) {
		return Platform_err();
	} else {
		return 0;
	}
	__RETCHK;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Truncate (LONGINT h, LONGINT limit)
{
	INTEGER rc;
	LONGINT oldpos;
	Platform_largeInteger();
	Platform_getFilePos(h, &oldpos, &rc);
	if (rc == 0) {
		return Platform_err();
	}
	Platform_setFilePointerEx(h, limit, Platform_seekset(), &rc);
	if (rc == 0) {
		return Platform_err();
	}
	if (Platform_setEndOfFile(h) == 0) {
		return Platform_err();
	}
	Platform_setFilePointerEx(h, oldpos, Platform_seekset(), &rc);
	if (rc == 0) {
		return Platform_err();
	}
	return 0;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Unlink (CHAR *n, LONGINT n__len)
{
	if (Platform_deleteFile(n, n__len) == 0) {
		return Platform_err();
	} else {
		return 0;
	}
	__RETCHK;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Chdir (CHAR *n, LONGINT n__len)
{
	INTEGER r;
	r = Platform_setCurrentDirectory(n, n__len);
	if (r == 0) {
		return Platform_err();
	}
	Platform_getCurrentDirectory((void*)Platform_CWD, 4096);
	return 0;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Rename (CHAR *o, LONGINT o__len, CHAR *n, LONGINT n__len)
{
	if (Platform_moveFile(o, o__len, n, n__len) == 0) {
		return Platform_err();
	} else {
		return 0;
	}
	__RETCHK;
}

/*----------------------------------------------------------------------------*/
void Platform_Exit (INTEGER code)
{
	Platform_exit(code);
}

/*----------------------------------------------------------------------------*/
static void Platform_errch (CHAR c)
{
	Platform_errc(c);
}

static void Platform_errln (void)
{
	Platform_errch(0x0d);
	Platform_errch(0x0a);
}

static void Platform_errposint (LONGINT l)
{
	if (l > 10) {
		Platform_errposint(__DIV(l, 10));
	}
	Platform_errch((CHAR)(48 + __MOD(l, 10)));
}

static void Platform_errint (LONGINT l)
{
	if (l < 0) {
		Platform_errch('-');
		l = -l;
	}
	Platform_errposint(l);
}

static void Platform_DisplayHaltCode (LONGINT code)
{
	switch (code) {
		case -1: 
			Platform_errstring((CHAR*)"Rider ReadBuf/WriteBuf transfer size longer than buffer.", (LONGINT)57);
			break;
		case -2: 
			Platform_errstring((CHAR*)"Index out of range.", (LONGINT)20);
			break;
		case -3: 
			Platform_errstring((CHAR*)"Reached end of function without reaching RETURN.", (LONGINT)49);
			break;
		case -4: 
			Platform_errstring((CHAR*)"CASE statement: no matching label and no ELSE.", (LONGINT)47);
			break;
		case -5: 
			Platform_errstring((CHAR*)"Type guard failed.", (LONGINT)19);
			break;
		case -6: 
			Platform_errstring((CHAR*)"Type equality failed.", (LONGINT)22);
			break;
		case -7: 
			Platform_errstring((CHAR*)"WITH statement type guard failed.", (LONGINT)34);
			break;
		case -8: 
			Platform_errstring((CHAR*)"SHORT: Value too large for shorter type.", (LONGINT)41);
			break;
		case -9: 
			Platform_errstring((CHAR*)"Heap interrupted while locked, but lockdepth = 0 at unlock.", (LONGINT)60);
			break;
		case -15: 
			Platform_errstring((CHAR*)"Type descriptor size mismatch.", (LONGINT)31);
			break;
		case -20: 
			Platform_errstring((CHAR*)"Too many, or negative number of, elements in dynamic array.", (LONGINT)60);
			break;
		default: 
			break;
	}
}

void Platform_Halt (LONGINT code)
{
	INTEGER e;
	Platform_HaltCode = code;
	if (Platform_HaltHandler != NIL) {
		(*Platform_HaltHandler)(code);
	}
	Platform_errstring((CHAR*)"Terminated by Halt(", (LONGINT)20);
	Platform_errint(code);
	Platform_errstring((CHAR*)"). ", (LONGINT)4);
	if (code < 0) {
		Platform_DisplayHaltCode(code);
	}
	Platform_errln();
	Platform_exit(__VAL(INTEGER, code));
}

/*----------------------------------------------------------------------------*/
void Platform_AssertFail (LONGINT code)
{
	INTEGER e;
	Platform_errstring((CHAR*)"Assertion failure.", (LONGINT)19);
	if (code != 0) {
		Platform_errstring((CHAR*)" ASSERT code ", (LONGINT)14);
		Platform_errint(code);
		Platform_errstring((CHAR*)".", (LONGINT)2);
	}
	Platform_errln();
	Platform_exit(__VAL(INTEGER, code));
}

/*----------------------------------------------------------------------------*/
void Platform_SetHalt (Platform_HaltProcedure p)
{
	Platform_HaltHandler = p;
}

/*----------------------------------------------------------------------------*/
static void Platform_TestLittleEndian (void)
{
	INTEGER i;
	i = 1;
	__GET((LONGINT)&i, Platform_LittleEndian, BOOLEAN);
}

__TDESC(Platform_FileIdentity__desc, 1, 0) = {__TDFLDS("FileIdentity", 40), {-8}};

export void *Platform__init(void)
{
	__DEFMOD;
	__REGMOD("Platform", 0);
	__INITYP(Platform_FileIdentity, Platform_FileIdentity, 0);
/* BEGIN */
	Platform_TestLittleEndian();
	Platform_HaltCode = -128;
	Platform_HaltHandler = NIL;
	Platform_TimeStart = Platform_Time();
	Platform_CWD[0] = 0x00;
	Platform_getCurrentDirectory((void*)Platform_CWD, 4096);
	Platform_PID = Platform_getpid();
	Platform_SeekSet = Platform_seekset();
	Platform_SeekCur = Platform_seekcur();
	Platform_SeekEnd = Platform_seekend();
	Platform_StdIn = Platform_getstdinhandle();
	Platform_StdOut = Platform_getstdouthandle();
	Platform_StdErr = Platform_getstderrhandle();
	Platform_nl[0] = 0x0d;
	Platform_nl[1] = 0x0a;
	Platform_nl[2] = 0x00;
	__ENDMOD;
}