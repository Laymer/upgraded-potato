# compiler
CPPFLAGS="-I$HOME/usr/include"
LDFLAGS="-L$HOME/usr/lib"
PKG_CONFIG_PATH="$HOME/usr/lib/pkgconfig:$HOME/usr/lib/x86_64-linux-gnu/pkgconfig:$HOME/usr/share/pkgconfig"
export CPPFLAGS LDFLAGS PKG_CONFIG_PATH

# linker
LD_LIBRARY_PATH="$HOME/usr/lib/x86_64-linux-gnu/"
PATH="$HOME/usr/bin:$PATH"
export LD_LIBRARY_PATH PATH

# gir
XDG_DATA_DIRS=$HOME/usr/share:$XDG_DATA_DIRS
export XDG_DATA_DIRS

# girepository-1.0
export GI_TYPELIB_PATH=$HOME/usr/lib/x86_64-linux-gnu/girepository-1.0

# gsetting
export GSETTINGS_SCHEMA_DIR=$HOME/usr/share/glib-2.0/schemas