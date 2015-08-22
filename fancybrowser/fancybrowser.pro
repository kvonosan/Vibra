QT      +=  webkitwidgets network widgets
HEADERS =   mainwindow.h
SOURCES =   main.cpp \
            mainwindow.cpp
RESOURCES =

# install
target.path = $$[QT_INSTALL_EXAMPLES]/webkitwidgets/fancybrowser
INSTALLS += target
