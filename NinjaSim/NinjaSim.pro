QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ninjasim/bomb_tile.cpp \
    ninjasim/direction.cpp \
    ninjasim/name_generator.cpp \
    ninjasim/player.cpp \
    ninjasim/simulation.cpp \
    ninjasim/tile.cpp

HEADERS += \
    ninjasim/arrow_tile.h \
    ninjasim/bomb_tile.h \
    ninjasim/booster_tile.h \
    ninjasim/box_tile.h \
    ninjasim/direction.h \
    ninjasim/empty_tile.h \
    ninjasim/goal_tile.h \
    ninjasim/mirror_tile.h \
    ninjasim/name_generator.h \
    ninjasim/pathway_tile.h \
    ninjasim/player.h \
    ninjasim/shuriken_tile.h \
    ninjasim/simulation.h \
    ninjasim/start_tile.h \
    ninjasim/tile.h \
    ninjasim/tile_type.h \
    ninjasim/wall_tile.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
