TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    $$PWD/DameGame \
    $$PWD/ihm

$$PWD/ihm.depends = $$PWD/DameGame
