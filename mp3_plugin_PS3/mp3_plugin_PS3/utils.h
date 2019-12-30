CDECL int _sys_printf(const char *fmt, ...);
#define printf _sys_printf

CDECL int _sys_snprintf(char *buffer, size_t len, const char *fmt, ...);
#define snprintf _sys_snprintf

CDECL int _sys_sprintf(char *buffer, const char *fmt, ...);
#define sprintf _sys_sprintf

CDECL int _sys_vprintf(const char *format, va_list arg);
#define vprintf _sys_vprintf

CDECL int _sys_vsnprintf(char* buffer, std::size_t buf_size, const char* format, va_list arg);
#define vsnprintf _sys_vsnprintf

CDECL int _sys_vsprintf(char *s, const char *format, va_list arg);
#define vsprintf _sys_vsprintf

CDECL void *_sys_malloc(size_t size);
#define malloc _sys_malloc

CDECL void _sys_free(void *ptr);
#define free _sys_free

CDECL void *_sys_memalign(size_t boundary, size_t size);
#define memalign _sys_memalign

CDECL void *_sys_memchr(const void *s, int c, size_t n);
#define memchr _sys_memchr

CDECL int _sys_memcmp(const void * s1, const void * s2, size_t n);
#define memcmp _sys_memcmp

CDECL void *_sys_memcpy(void *dest, const void *src, size_t n);
#define memcpy _sys_memcpy

CDECL void *_sys_memset(void *m, int c, size_t n);
#define memset _sys_memset

CDECL void *_sys_memmove(void *str1, const void *str2, size_t n);
#define memmove _sys_memmove

CDECL char *_sys_strcat(char *dest, const char *src);
#define strcat _sys_strcat

CDECL char *_sys_strchr(const char *s, int c);
#define strchr _sys_strchr

CDECL int _sys_strcmp(const char * s1, const char * s2);
#define strcmp _sys_strcmp

CDECL char *_sys_strcpy(char *dest, const char *src);
#define strcpy _sys_strcpy

CDECL size_t _sys_strlen(const char *str);
#define strlen _sys_strlen

CDECL int _sys_strncasecmp(const char *s1, const char *s2, size_t n);
#define strncasecmp _sys_strncasecmp

CDECL char *_sys_strncat(char *dest, const char *src, size_t n);
#define strncat _sys_strncat

CDECL int _sys_strncmp(const char * s1, const char * s2, size_t n);
#define strncmp _sys_strncmp

CDECL char *_sys_strncpy(char *dest, const char *src, size_t n);
#define strncpy _sys_strncpy

CDECL char *_sys_strrchr(const char *s, int c);
#define strrchr _sys_strrchr

CDECL int _sys_tolower(int c);
#define tolower _sys_tolower

CDECL int _sys_toupper(int c);
#define toupper _sys_toupper

#define bzero(s, n) memset((s), 0, (n))
#define bcopy(s1, s2, n) memmove((s2), (s1), (n))

































#define GAME_TOC 0x014CF618

struct opd_s
{
	uint32_t sub;
	uint32_t toc;
};

opd_s ParseAddr(uint32_t sub)
{
	opd_s opd;
	opd.sub = sub;
	opd.toc = GAME_TOC;
	printf("opd_s.sub = 0x%X | opd_s.toc = 0x%X\n", opd.sub, opd.toc);
	return opd;
}
template <typename T>
T(*call(unsigned int address))(...)
{
	T(*func)(...) = (T(*)(...))&ParseAddr(address);
	return func;
}


