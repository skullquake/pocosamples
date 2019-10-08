poco hello

installation (msys2)
```
pacman -S mingw-w64-i686-poco mingw-w64-x86_64-poco 
```
relevant libraries:
```
libPocoCrypto.dll.a
libPocoData.dll.a
libPocoDataMySQL.dll.a
libPocoDataODBC.dll.a
libPocoDataSQLite.dll.a
libPocoEncodings.dll.a
libPocoFoundation.dll.a
libPocoJSON.dll.a
libPocoNet.dll.a
libPocoNetSSL.dll.a
libPocoRedis.dll.a
libPocoUtil.dll.a
libPocoXML.dll.a
libPocoZip.dll.a
```

installation termux

* build from source
* fix shm_ references (just replaced with open)
* linking with -llog is also required

reference

[pocoproject.org/docs/00100-GuidedTour](https://pocoproject.org/docs/00100-GuidedTour.html)
