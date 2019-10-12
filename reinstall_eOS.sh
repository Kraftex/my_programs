#!/bin/bash

# Script to reinstall all programs I had in ElementaryOS
#option=w

# Functions
function check_or_install
{
    echo $1 && dpkg -s $1 2> logs.log | grep "Status" || sudo apt-get install $1
}

function inst_popcorn
{
    sudo apt update && sudo apt install libcanberra-gtk-module libgconf-2-4
    wget -O popcorn.tar.xz "https://get.popcorntime.sh/build/Popcorn-Time-0.3.10-Linux-64.tar.xz"
    sudo mkdir /opt/popcorntime
    sudo tar xJf popcorn.tar.xz -C /opt/popcorntime
    sudo ln -sf /opt/popcorntime/Popcorn-Time /usr/bin/Popcorn-Time
    sudo touch /usr/share/applications/popcorntime.desktop
    sudo echo "[Desktop Entry]" > /usr/share/applications/popcorntime.desktop
    sudo echo "Version = 3.10" >> /usr/share/applications/popcorntime.desktop
    sudo echo "Type = Application" >> /usr/share/applications/popcorntime.desktop
    sudo echo "Terminal = false" >> /usr/share/applications/popcorntime.desktop
    sudo echo "Name = Popcorn Time" >> /usr/share/applications/popcorntime.desktop
    sudo echo "Exec = /usr/bin/Popcorn-Time" >> /usr/share/applications/popcorntime.desktop
    sudo echo "Icon = /opt/popcorntime/src/app/images/icon.png" >> /usr/share/applications/popcorntime.desktop
    sudo echo "Categories = Application;" >> /usr/share/applications/popcorntime.desktop
    rm popcorn.tar.xz
}

function inst_recomends
{
    inst_others
    inst_fish_OMF
    inst_dr_java
    inst_discord
    inst_steam
    inst_mesa
    inst_flatpak
    inst_flatpak_progs
    conf_fish
}

function inst_wine
{
    if cat /etc/*-release | grep "bionic"
    then
        wget "https://download.opensuse.org/repositories/Emulators:/Wine:/Debian/xUbuntu_18.04/Release.key"
        sudo apt-key add Release.key
        sudo apt-add-repository 'deb https://download.opensuse.org/repositories/Emulators:/Wine:/Debian/xUbuntu_18.04/ ./'
        sudo apt update
        rm Release.key
        sudo dpkg --add-architecture i386
        wget -nc https://dl.winehq.org/wine-builds/winehq.key
        sudo apt-key add winehq.key
        sudo apt-add-repository 'deb https://dl.winehq.org/wine-builds/ubuntu/ bionic main'
        sudo apt-get update
        sudo apt install --install-recommends winehq-staging
    else
        echo "Your version isn't 18.04. https://wiki.winehq.org/Ubuntu"
    fi
}

function inst_builds
{
    check_or_install build-essential
}

# Rework
function inst_git
{
    check_or_install git
}

function inst_dr_java
{
    if -d "~/DrJava"
    then
        wget -O ~/DrJava/dr_java.jar "https://sourceforge.net/projects/drjava/files/1. DrJava Stable Releases/drjava-beta-20190813-220051/drjava-beta-20190813-220051.jar"
    else
        mkdir ~/DrJava
        wget -O ~/DrJava/dr_java.jar "https://sourceforge.net/projects/drjava/files/1. DrJava Stable Releases/drjava-beta-20190813-220051/drjava-beta-20190813-220051.jar"
    fi
    if echo "fish" && dpkg -s fish | grep "Status"
    then
        echo "alias drjava=\"java -jar ~/DrJava/dr_java.jar\"" >> ~/.config/fish/config.fish
    else
        echo "alias drjava=\"java -jar ~/DrJava/dr_java.jar\"" >> ~/.bash_aliases
    fi
}

function conf_drjava
{
    if -a "~/.drjava"
    then
        rm "~/.drjava"
        touch "~/.drjava"
    else
        touch "~/.drjava"
    fi
    echo "#DrJava configuration file" > ~/.drjava
    echo "#Tue Oct 01 22:12:56 CEST 2019" >> ~/.drjava
    echo "javac.location = /home/kraftex/DrJava/jdk1.8.0_181/lib/tools.jar" >> ~/.drjava
    echo "extra.classpath = /home/kraftex/DrJava/lib/stdlib.jar:/home/kraftex/DrJava/lib:/home/kraftex/DrJava/lib/CorrectorOffline.jar:/home/kraftex/DrJava/lib/junit-4.13-beta-2.jar:/home/kraftex/DrJava/lib/tads1819.jar:/home/kraftex/DrJava/lib/aedlib.jar" >> ~/.drjava
    echo "definitions.normal.color = #cccccc" >> ~/.drjava
    echo "definitions.keyword.color = #60ff60" >> ~/.drjava
    echo "definitions.type.color = #ff80ff" >> ~/.drjava
    echo "definitions.comment.color = #80a0ff" >> ~/.drjava
    echo "definitions.double.quoted.color = #ffa0a0" >> ~/.drjava
    echo "definitions.single.quoted.color = #ffa000" >> ~/.drjava
    echo "system.out.color = #00cc33" >> ~/.drjava
    echo "definitions.background.color = #000000" >> ~/.drjava
    echo "definitions.line.number.background.color = #000000" >> ~/.drjava
    echo "definitions.line.number.color = #fff700" >> ~/.drjava
    echo "definitions.match.color = #009999" >> ~/.drjava
    echo "compiler.error.color = #c27b00" >> ~/.drjava
    echo "font.main = Fixedsys Excelsior 3.01-16" >> ~/.drjava
    echo "font.line.numbers = Fixedsys Excelsior 3.01-16" >> ~/.drjava
    echo "font.doclist = Monospaced-14" >> ~/.drjava
    echo "font.toolbar = -14-12" >> ~/.drjava
    echo "lineenum.enabled = true" >> ~/.drjava
    echo "look.and.feel = com.jgoodies.looks.plastic.Plastic3DLookAndFeel" >> ~/.drjava
    echo "key.delete.next = [shift DELETE]" >> ~/.drjava
    echo "key.delete.previous = [shift BACK_SPACE]" >> ~/.drjava
    echo "interactions.exit.prompt = false" >> ~/.drjava
    echo "quit.prompt = false" >> ~/.drjava
    echo "save.before.compile = true" >> ~/.drjava
    echo "indent.level = 4" >> ~/.drjava
    echo "recent.files = [/home/kraftex/DrJava/lib/linux/NormalDistribution.java,/home/kraftex/DrJava/lib/linux/Tools.java,/home/kraftex/DrJava/lib/linux/Test.java,/home/kraftex/IdeaProjects/AEDLab01/src/test/java/TesterLab1.java]" >> ~/.drjava
    echo "window.height = 1020" >> ~/.drjava
    echo "window.width = 1918" >> ~/.drjava
    echo "window.x = 0" >> ~/.drjava
    echo "window.y = 60" >> ~/.drjava
    echo "doc.list.width = 205" >> ~/.drjava
    echo "last.dir = /home/kraftex/DrJava/lib/linux/NormalDistribution.java" >> ~/.drjava
    echo "last.interactions.dir = /home/kraftex/DrJava/lib/linux" >> ~/.drjava
    echo "slave.jvm.xmx = 2048" >> ~/.drjava
    echo "dialog.completeword.scan.class.files = true" >> ~/.drjava
    echo "tabbedpanes.state = 960 540 700 400" >> ~/.drjava
    echo "new.version.notification.last = 1569747844237" >> ~/.drjava
}

function inst_fish_OMF
{
    inst_git
    check_or_install fish
    check_or_install curl
    curl -L https://get.oh-my.fish
}

# Last
function conf_fish
{
    if echo "fish" && dpkg -s fish | grep "Status"
    then
        chsh -s /usr/bin/fish || whereis fish
        fish
        omf install scorphish
        echo "set -g theme_display_rust yes" >> ~/.config/fish/config.fish
        omf reload
    fi
}

function inst_discord
{
    wget -O discord.deb "https://discordapp.com/api/download?platform=linux&format=deb"
    sudo dpkg -i discord.deb
    rm discord.deb
}

function inst_lutris
{
    sudo add-apt-repository ppa:lutris-team/lutris
    sudo apt-get update
    sudo apt-get install lutris
}

function inst_steam
{
    sudo apt install steam-installer
}

function inst_java
{
    sudo add-apt-repository ppa:linuxuprising/java
    sudo apt-get update
    sudo apt-get install oracle-java11-installer
    #Mejorar con un wget -O drJava paginaDeDescagaDeDrJava...
}

function inst_open_jdk
{
    sudo add-apt-repository ppa:openjdk-r/ppa
    sudo apt update
    sudo apt install openjdk-11-jdk
}

function inst_minecraft
{
    #echo "I don't know how. https://www.minecraft.net/en-us/"
    wget -O minecraft.deb "https://launcher.mojang.com/download/Minecraft.deb"
    sudo dpkg -i minecraft.deb
    rm minecraft.deb
}

function inst_mesa_drivers
{
    sudo add-apt-repository ppa:ubuntu-x-swat/updates
    sudo apt-get update
    sudo apt-get dist-upgrade
    sudo apt-get mesa-utils
}

function inst_vulkan_drivers
{
    sudo add-apt-repository ppa:paulo-miguel-dias/pkppa
    sudo apt update && sudo apt upgrade
    sudo apt install mesa-vulkan-drivers
    echo "Support for 32bits games"
    echo "Do you want to install[S|n]?"
    read var
    case $var in
        s|S|'' )
            sudo apt install libgl1-mesa-glx:i386 libgl1-mesa-dri:i386
            sudo apt install mesa-vulkan-drivers:i386
            ;;
    esac
}

function inst_flatpak
{
    sudo apt-get install software-properties-common --no-install-recommends
    sudo add-apt-repository ppa:alexlarsson/flatpak
    sudo apt-get update
    sudo apt-get install flatpak
    flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
}

function inst_flatpak_progs
{
    if echo "flatpak" && dpkg -s flatpak | grep "Status"
    then
        flatpak install flathub org.libreoffice.LibreOffice
        flatpak install flathub org.kde.krita
        flatpak install flathub org.gimp.GIMP
        flatpak install flathub org.inkscape.Inkscape
        flatpak install flathub org.vinszent.GnomeTwitch
        flatpak install flathub org.katawa_shoujo.KatawaShoujo
        flatpak install flathub org.jetbrains.IntelliJ-IDEA-Community
        flatpak install flathub com.github.libresprite.LibreSprite
    else
        echo "You don't have installed 'flatpak'"
    fi
}

function inst_corretto
{
    wget -O java-corretto.deb "https://d3pxv6yz143wms.cloudfront.net/8.222.10.1/java-1.8.0-amazon-corretto-jdk_8.222.10-1_amd64.deb"
    sudo apt-get install java-common
    sudo dpkg -i java-corretto.deb
    rm java-corretto.deb
    java -version
    echo "If you can see that it doesn't appear 'Corretto' in the lines above, you must try the below commands.\n"
    echo "sudo update-alternatives --config java"
    echo "sudo update-alternatives --config javac"
}

function inst_others
{
    check_or_install clang
    check_or_install htop
    check_or_install git
    check_or_install curl
    check_or_install synaptic
    check_or_install neofetch
    check_or_install vim-gtk
    check_or_install rust
    check_or_install gcc
}

sudo apt-get update && sudo apt-get upgrade
sudo apt-get autoremove

while : #"$option" != "x"
do
    echo "What do you want to install?       "
    echo "    a) DrJava (Rec)                " # Done!
    echo "    b) Build-utils                 " # Done!
    echo "    c) Popcorn                     " # Done!
    echo "    d) Discord (Rec)               " # Done!
    echo "    e) Wine (Staging)              " # Done!
    echo "    f) Flatpak (Rec)               " # Done!
    echo "    g) Git (Rec)                   " # Done!
    echo "    h) Fish & OMF (Rec)            " # Done!
    echo "    i) Config OMF (Rec)            " # Done!
    echo "    j) Java 11                     " # Done!
    echo "    k) Steam (Rec)                 " # Done!
    echo "    l) Lutris                      " # Done!
    echo "    m) Minecraft                   " # Done!
    echo "    n) Mesa Drives (Rec)           " # Done!
    echo "    o) OpenJDK 11                  " # Done!
    echo "    p) Apps from flatpak           " # Done!
    echo "    q) Corretto 8 (OpenJDK 8)      " # Done!
    echo "    r) Install recomends (Rec)     " # Done!
    echo "    s) Vulkan Drivers              " # Done!
    echo "    t) Others programs (Rec)       " # Done! # Clag, htop, cosas de ubuntu...
    echo "    u) Aseprite (Not works)        " # Done!
    echo "    v) GHLD & GTKWaves (VHDL)      " # Done!
    echo "    w) LibreSprite (Flathub)       " # Done!
    echo "    y) Assembly MC88110            " # Done!
    echo "    z) Godot (Standart edition)    " # Done!
    echo ""
    echo "    x) Nothing and exit            " # Done!

    read option
    case $option in
        a)
            inst_dr_java
            ;;
        b)
            inst_builds
            ;;
        c)
            inst_popcorn
            ;;
        d)
            inst_discord
            ;;
        e)
            inst_wine
            ;;
        f)
            inst_flatpak
            ;;
        g)
            inst_git
            ;;
        h)
            inst_fish_OMF
            ;;
        i)
            conf_fish
            ;;
        j)
            inst_java
            ;;
        k)
            inst_steam
            ;;
        l)
            inst_lutris
            ;;
        m)
            inst_minecraft
            ;;
        n)
            inst_mesa_drivers
            ;;
        o)
            inst_open_jdk
            ;;
        p)
            inst_flatpak_progs
            ;;
        q)
            inst_corretto
            ;;
        r)
            inst_recomends
            ;;
        s)
            inst_vulkan_drivers
            ;;
        t)
            inst_others
            ;;
        u)
            check_or_install git
            git clone https://github.com/aseprite/aseprite.git
            cd aseprite
            dir_aseprite=${PWD}
            check_or_install g++
            check_or_install cmake
            check_or_install ninja-build
            check_or_install libx11-dev
            check_or_install libxcursor-dev
            check_or_install libgl1-mesa-dev
            check_or_install libfontconfig1-dev
            #Install 'Skia'
            mkdir $HOME/deps
            cd $HOME/deps
            git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
            git clone -b aseprite-m71 https://github.com/aseprite/skia.git
            export PATH="${PWD}/depot_tools:${PATH}"
            cd skia
            python tools/git-sync-deps
            gn gen out/Release --args="is_debug=false is_official_build=true skia_use_system_expat=false skia_use_system_icu=false skia_use_system_libjpeg_turbo=false skia_use_system_libpng=false skia_use_system_libwebp=false skia_use_system_zlib=false"
            ninja -C out/Release skia
            #'Skia' installed, then compile 'aseprite'
            cd "$dir_aseprite"
            mkdir build
            cd build
            cmake \
              -DCMAKE_BUILD_TYPE=RelWithDebInfo \
              -DLAF_OS_BACKEND=skia \
              -DSKIA_DIR=$HOME/deps/skia \
              -DSKIA_OUT_DIR=$HOME/deps/skia/out/Release \
              -G Ninja \
              ..
            ninja aseprite
            ;;
        v)
            # Code from: https://gist.github.com/mathieucaroff/73ccbd30638d9b37b7129a7b7b8d7726
            # download-buidl-and-install-ghdl.sh
            #
            # It took about 5 minutes on my laptop (2018-09-28).

            sudo apt update
            sudo apt install -y git make gnat zlib1g-dev
            git clone https://github.com/ghdl/ghdl
            cd ghdl
            ./configure --prefix=/usr/local
            make
            sudo make install
            echo "$0: All done!"

            # See the quick start guide to learn basic usage
            # https://ghdl.readthedocs.io/en/latest/using/QuickStartGuide.html
            # 
            # The two main commands are `ghdl -a` (analyse) and `ghdl -r` (run)
            # If you copied the full adder example from the quick start guide into
            # `full-adder.vhd` and `full-adder_tb.vhd`, you can use ghdl like so:
            #
            # ghdl -a full-adder.vhd full-adder_tb.vhd
            # ghdl -r adder_tb
            # > full-adder_tb.vhd:55:16:@8ns:(assertion note): end of test
            #

            # Install 'gtk-waves' for view the waves that ghdl produce...
            sudo apt-get install gtkwave
            echo "Instructions to watch thw waves for components in GHDL(VHDL)" > README_GHDL.txt
            echo "" >> README_GHDL.txt
            echo "For 'add'/'analyze' components to work: ghdl -a name_file.vhdl name_other_file.vhdl ..." >> README_GHDL.txt
            echo "" >> README_GHDL.txt
            echo "For run and export the waves: ghdl -r name_entity_testbench --vcd=name_file_waves.vcd" >> README_GHDL.txt
            echo "" >> README_GHDL.txt
            echo "For run and export the waves with stop-time: ghdl -r name_entity_testbench --stop-time=NUMmag --vcd=name_file_waves.vcd" >> README_GHDL.txt
            echo "                                                                                     NUM: A number" >> README_GHDL.txt
            echo "                                                                                        mag: The magnitude, such as 'ps', 'fp', 'ms', 'ns'" >> README_GHDL.txt
            echo "For watch waves: gtkwave name_file_waves.vcd" >> README_GHDL.txt
            ;;
        w)
            if echo "flatpak" && dpkg -s flatpak | grep "Status"
            then
                flatpak install flathub com.github.libresprite.LibreSprite
            else
                echo "You don't have installed 'flatpak'"
            fi
            ;;
        y)
            curl "https://web.archive.org/web/20110724011151/http://www.datsi.fi.upm.es/88110/88k_Linux_Static.tar.gz" --output assembly_mc88110.tar.gz
            tar xzf assembly_mc88110.tar.gz
            rm assembly_mc88110.tar.gz
            cd EM88110
            sudo ./INSTALL
            ;;
        z)
            wget -O godot.zip "https://downloads.tuxfamily.org/godotengine/3.1.1/Godot_v3.1.1-stable_x11.64.zip"
            if -d "~/Godot"
            then
                unzip godot.zip -d "~/Godot"
            else
                mkdir "~/Godot"
                unzip godot.zip -d "~/Godot"
            fi
            ;;
        x)
            if -a "logs.log"
            then
                rm logs.log
            fi
            echo "Goodbye"
            break
            ;;
        *)
            echo "I don't know that command."
    esac

done

