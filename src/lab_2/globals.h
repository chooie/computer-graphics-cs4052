#pragma once

#ifdef __MAIN__
    #define __EXTERN(type, name, value)     type name = value
#else
    #define __EXTERN(type, name, value)     extern type name;
#endif

__EXTERN(volatile float, transX, 0.0f);
__EXTERN(volatile float, transY, 0.0f);
__EXTERN(volatile float, transZ, 0.0f);

__EXTERN(volatile float, rotX, 0.0f);
__EXTERN(volatile float, rotY, 0.0f);
__EXTERN(volatile float, rotZ, 0.0f);

__EXTERN(volatile float, scaleX, 1.0f);
__EXTERN(volatile float, scaleY, 1.0f);
__EXTERN(volatile float, scaleZ, 1.0f);
