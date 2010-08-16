TARGET = balda
QT += core \
    gui \
    network
CONFIG += precompile_header

# PRECOMPILED_HEADER = prec.h
HEADERS += prec.h \
    cell_item.h \
    game.h \
    Server.h \
    visual.h \
    scorepanelitem.h
SOURCES += cell_item.cpp \
    game.cpp \
    Server.cpp \
    main.cpp \
    visual.cpp \
    scorepanelitem.cpp
FORMS += game.ui
RESOURCES += 
FORMS += 
