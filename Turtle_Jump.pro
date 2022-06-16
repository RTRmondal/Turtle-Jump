TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

# -CHANGE THE PATH TO SFML LIBRARY ACCORDINGLY--

INCLUDEPATH += "C:/Users/Ruman/Documents/SFML-2.5.1/include"

LIBS += -L"C:/Users/Ruman/Documents/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}
