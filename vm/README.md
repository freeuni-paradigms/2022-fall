# 0) MacOS-ზე გააზიარეთ დავალებების დირექტორია ქსელში
![MacOS Share](/#8.png)

```sh
# 1) დააყენეთ brew პაკეტების მენეჯერი
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# 2) დააყენეთ qemu ვირტუალიზაციის ხელსაწყო
brew install qemu

# 3) შექმენით ვირტუალური დისკი ვირტუალური მანქანისთვის
qemu-img create hd.img 10G

# 4) გადმოწერეთ Ubuntu-ს საინსტალაციო დისკი
brew install wget
wget https://releases.ubuntu.com/22.04.1/ubuntu-22.04.1-live-server-amd64.iso

# 5) დააყენეთ Ubuntu ვირტუალურ მანქანაზე - მიყევით ქვემოთ ახსნილ დაყენების ინსტრუქციას
qemu-system-x86_64 -cdrom ubuntu-22.04.1-live-server-amd64.iso -hda hd.img -smp 4 -m 4G -serial stdio

# 6) ჩართეთ ვირტუალური მანქანა
qemu-system-x86_64 -hda hd.img -smp 4 -m 4G -net user,hostfwd=tcp::10022-:22 -net nic -serial stdio

# 7) ვირტუალურ მანქანაზე დააყენეთ საჭირო ხელსაწყოები
sudo apt-get update
sudo apt-get install gcc g++ make git valgrind cifs-utils

# 8) ვირტუალურ მანქანაზე შექმენით სკრიპტი რომელიც MacOS-ის დავალებების დირექტორიას გამოაჩენს ვირტუალურ მანქანაზე
echo "mount -t cifs //192.168.100.2/paradigms $(pwd)/classroom -o username=lekva" > connect.sh
chmod +x connect.sh
```



# Ubuntu-ს ინსტალაცია
![Ubuntu Server Minimized](/#1.png)
![Storage Configuration](/#2.png)
![Storage Configuration Continue](/#3.png)
![User](/#4.png)
![OpenSSH Server](/#5.png)
![Skip all Snaps](/#6.png)
![Reboot on Done](/#7.png)


# ქვემოთ ჯერ-ჯერობით ყურადღებას ნუ მიაქცევთ

sudo sed -i 's|http://ge.|http://|g' /etc/apt/sources.list
sudo ./connect.sh

cd ~/classroom/hw/01-rsg
sudo make test_all
