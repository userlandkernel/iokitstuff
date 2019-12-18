# IOKit Stuff
Please contribute by reversing the kexts and implementing easy to use methods around the userclients.  
This is a project giving easy level access to kernel drivers by implementing around the complex scalar input and selector methods of kernel drivers part of the IOKit. 
One day it may or may not enhance bug life.  

## Whats in it
- IOAccelerator (Weird shit going on in there, crashed the GPU while fuzzing).  
- IOSurfaceRoot (Not even halfly implemented, too lazy as the framework's private headers should be enough).  
- IOMobileFramebuffer (Implemented as much as I know about).  

## IOAccelerator
- Used for graphics acceleration
- Used together with IOSurfaces and commonly seen in Metal.  
- Backed by physmem.  
- Implemented to be powered by the GPU
- Seems like when the GPU triggers a pagefault XNU handles it and continues! (Means probably perfect stability for exploitation some day).  

## IOMobileFramebuffer
- Used for inverted colors, whitepoint adaptivity, gamma shadings (like nightshift) and brightness.  

## IOSurface
- Probably for encoding views / windows and scalings etc, have to do a bit more research on it.  


## Compiling
If you do not know what you are doing compiling the project will be a pain in the ass.  
To use the private headers and frameworks as I did in the project I installed theos SDKS in my Xcode folder.  
It will also require copying over headers from the internet (class-dump) and the MacOS SDK.  
You can always file an issue if you're stuck but do note that I will not aid in getting the headers in the right place etc, the community however might be able to help with that.  

## Additional credits & Thanks
- Luca Todesco for pointing me out that coffee is important (I screwed up algorithms when I was tired).  
- [TheiPhoneDevWiki](https://iphonedevwiki.net/)
- Google Project Zero (Blog, August 2019).  
- Apple Inc. (Why? They permit the connections to these drivers from within the sandbox without requiring entitlements).  
- OSXFuzz (The machaids contain some methods from OSXFuzz for future plans)
