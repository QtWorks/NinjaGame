TEMPLATE = subdirs

SUBDIRS += \
    NinjaSim \
    NinjaCLI \
    NinjaGUI

NinjaCLI.depends = NinjaSim
NinjaGUI.depends = NinjaSim
