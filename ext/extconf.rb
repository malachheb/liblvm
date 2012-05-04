
require 'mkmf'

have_header("lvm2app.h")
have_header("sys/types.h")
have_header("libdevmapper.h")
#have_header("sys/mount.h");
$LOCAL_LIBS = "/lib/libdevmapper.so.1.02.1  /lib/liblvm2app.so.2.2" 
create_makefile("liblvm") 
