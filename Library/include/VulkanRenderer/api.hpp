
#ifndef VULREN_EXPORT_H
#define VULREN_EXPORT_H

#ifdef VULREN_STATIC_DEFINE
#  define VULREN_EXPORT
#  define VULREN_NO_EXPORT
#else
#  ifndef VULREN_EXPORT
#    ifdef VulkanRenderer_EXPORTS
        /* We are building this library */
#      define VULREN_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VULREN_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VULREN_NO_EXPORT
#    define VULREN_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VULREN_DEPRECATED
#  define VULREN_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef VULREN_DEPRECATED_EXPORT
#  define VULREN_DEPRECATED_EXPORT VULREN_EXPORT VULREN_DEPRECATED
#endif

#ifndef VULREN_DEPRECATED_NO_EXPORT
#  define VULREN_DEPRECATED_NO_EXPORT VULREN_NO_EXPORT VULREN_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VULREN_NO_DEPRECATED
#    define VULREN_NO_DEPRECATED
#  endif
#endif

#endif /* VULREN_EXPORT_H */
