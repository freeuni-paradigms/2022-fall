# 0) MacOS-ზე გააზიარეთ დავალებების დირექტორია ქსელში
![MacOS Share](https://github.com/freeuni-paradigms/2022-fall/raw/main/vm/%238.png)
![MacOS Share](https://github.com/freeuni-paradigms/2022-fall/raw/main/vm/%239.png)

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

# 7) დაუკავშირდით ვირტუალურ მანქანას MacOS-ის ტერმინალიდან, მოთხოვნილ პაროლშიც შეიყვანეთ paradigms
#    შეგიძლიათ რომ ვირტუალური მანქანის ჩართვის შემდეგ მასში ყოველთვის SSH-ით შეხვიდეთ.
ssh -p 10022 paradigms@localhost

# 8) ვირტუალურ მანქანაზე დააყენეთ საჭირო ხელსაწყოები
sudo apt-get update
sudo apt-get install gcc g++ make git valgrind cifs-utils

# 9) შექმენით კლასრუმის დირექტორია
cd ~/
mkdir classroom

# 10) ვირტუალურ მანქანაზე შექმენით სკრიპტი რომელიც MacOS-ის დავალებების დირექტორიას გამოაჩენს ვირტუალურ მანქანაზე
#    ყურადღება მიაქციეთ IP მისამართს და მომხმარებლის სახელს. IP მისამართში უნდა შეიყვანოთ თქვენი მანქანის მისამართი რომელიც
#    ნაჩვენებია პირველ სურათზე ზემოთ, ხოლო სახელში თქვენი MacOS-ის მომხმარებლის username
echo "mount -t cifs //192.168.100.2/paradigms $(pwd)/classroom -o username=lekva" > connect.sh
chmod +x connect.sh
```

# ვირტუალური მანქანის გათიშვა
```sh
sudo shutdown -h now
```

# ვირტუალური მანქანის გადატვირთვა
```sh
sudo shutdown -r now
```

# პრობლემების შემთხვევაში
## თუ apt-get არ მუშაობს ვირტუალურ მანქანაზე
```sh
sudo sed -i 's|http://ge.|http://|g' /etc/apt/sources.list
sudo sed -i 's|http://us.|http://|g' /etc/apt/sources.list

# ქვედა ბრძანება აღარ უნდა აგდებდეს შეცდომას
sudo apt-get update
```

# Ubuntu-ს ინსტალაცია
![Ubuntu Server Minimized](https://github.com/freeuni-paradigms/2022-fall/raw/main/vm/%231.png)
![Storage Configuration](https://github.com/freeuni-paradigms/2022-fall/raw/main/vm/%232.png)
![Storage Configuration Continue](https://github.com/freeuni-paradigms/2022-fall/raw/main/vm/%233.png)
## მომხმარებლის ყველა ვერლში (პაროლშიც) შეიყვანეთ paradigms
![User](https://github.com/freeuni-paradigms/2022-fall/raw/main/vm/%234.png)
![OpenSSH Server](https://github.com/freeuni-paradigms/2022-fall/raw/main/vm/%235.png)
![Skip all Snaps](https://github.com/freeuni-paradigms/2022-fall/raw/main/vm/%236.png)
![Reboot on Done](https://github.com/freeuni-paradigms/2022-fall/raw/main/vm/%237.png)

# ქვემოთ ჯერ-ჯერობით ყურადღებას ნუ მიაქცევთ
sudo ./connect.sh

cd ~/classroom/hw/01-rsg
sudo make test_all
