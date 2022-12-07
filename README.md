# Inventory Manager Project

## Team Members
- Noah Shoap - nshoap-utk
- Vincent Broda - vbroda17
- Joseph Wehby - josephwehby
- Jon Graham - Brenaren
- Jennifer Hulen - jhulen

![Inventory Manager Logo](./logo128x128.png)

## Program Description
Inventory Manager aims to be a program that allows your average small business owner to keep track of their inventory and change it how they see fit.
A built in point of sale system is also provided so that businesses don't have to worry about manually tracking sales or trying to use Inventory Manager with another point of sale system.  In addition to these basic features, Inventory Manager also provides features such as sales comparisons or sales suggestions to help businesses stay on top of discounting poor selling items.

## Download, Install, and Run

## These installation instructions are for Ubuntu.
I'm on macOS, but I tested these instructions in a Ubuntu VM and was able to successfully get our project built.
If you run into any issues, just email me at nshoap@vols.utk.edu.


### Install Needed Packages
```
sudo apt update
sudo apt upgrade
sudo apt install git build-essential cmake
sudo apt install cmake qt6-base-dev libgl1-mesa-dev qtcreator
sudo apt install libxkbcommon libvulkan1 mesa-vulkan-drivers vulkan-utils libvulkan-dev
```

### Download
You'll need to have added a SSH key to github before you can clone our repo.
Everyone should have permission to clone, but if there's any permission issue email me and I will fix.
- Clone this repo: ```git clone git@github.com:QT-Pies/inventory-project.git```
- Checkout gui-main: ```git checkout gui-main```

### Qt Installation
#### Before you start
Firstly, all Qt development for this project is going to be done on UNIX systems -- it hasn't been built on Windows natively.  

If you're on Windows 11 build 22000 or higher, you can run GUI programs through WSL natively.

Otherwise, if you are on Windows 10, I believe there are ways to do it anyways, but not officially supported.

I'd suggest probably just spinning up a Ubuntu VM through VMWare or something.

##### Grabbing a Qt Installer
1. Head over to [this link](https://login.qt.io/register) and create a Qt account.
2. Grab the ```.run``` installer for Linux from [here](https://www.qt.io/download-thank-you?os=linux&hsLang=en).

###### WSL Special Stuff (Skip if using native Ubuntu install)
- We need to copy over the install file you just downloaded, and run it from WSL.
- Check where your file is on your Windows file system, then open up a WSL window and copy the file.

###### Example
Let's say my download is at ```C:\Users\Noah\Downloads\qt-unified-linux-x64-4.4.2-online.run```

If I wanted to run this on my Ubuntu WSL install, I'd copy it over (probably not needed to copy) to that filesystem and run it, like so:
```
cp /mnt/c/Users/Noah/Downloads/qt-unified-linux-x64-4.4.2-online.run .
./qt-unified-linux-x64-4.4.2-online.run
```

If your WSL GUI programs are working properly, this should open up an install window.

You'll need to create a Qt account -- login with that account.

In the ```Installation Folder``` stage, check ```Qt 6.4 for desktop development```.

Once this installer is finished, Qt should be installed.

### Building program
Now that you've cloned our repo, installed Qt, you can build the GUI branch.
Run the following commands to build the program:
```
cd inventory-project # or whatever path you cloned the repo to
cmake CMakeLists.txt
cmake --build .
```

### Running the program

Assuming it builds successfully, run it like so: ```./bin/main 0 CSVInput/good_inventory.csv```

This should open up a 960x540 window that initializes to a login screen.

### Using the program

The default account credentials are admin, admin.

You can create other users later in the program.

Once you login, you'll be taken to an inventory view.

This view shows you the inventory that you opened.  You can update the text of the entries,
and the inventory will be updated.  This input is validated.

On the left of the screen, you have the various views of the program.  In order, they are:
- Inventory
- Point of Sales
- Sales Information
- Create / Update Users
- Welcome / About Screen
- Exit

Clicking these buttons will take you to the corresponding screen.

Each view is rather straightforward and typically consists of some text and buttons for you
to interact with.

#### Inventory View
On the inventory view, you can add / remove items.  The displayed inventory is loaded once, so added items won't be shown until restart.

#### Point of Sales View
The point of sales view you can add items to the transaction by either ID or Name -- you don't need to provide both.
Enter the quantity you want to sell for this item, and then when you're finished with the transaction, hit pay.

#### Sales Information (Sales Comparisons & Suggestions) View
The Sales Information view has various buttons you can click that will display information about how the current month compares to previous months.

#### Create / Update Users View
The Create / Update users view is similar to the login screen -- except you can now create other users, or update user permissions.

#### About Screen
The about screen contains just some simple text and serves no purpose for the end user.

#### Exit Button
The exit button will exit the program, but you can just close the window.

### License Information
Our license can be found [here](https://github.com/QT-Pies/inventory-project/blob/main/license.txt).
