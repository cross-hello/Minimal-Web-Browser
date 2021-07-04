## Minimal Web Browser 
Not HTML render, Not Java interpretation, Not HTTPS, Just a simple http web browser. The browser base on GTK2.0 and Berkeley Socket~

### Compile?
#### needing library

- GTK2.0
In Ubuntu you could type in following to install:
```Shell
sudo apt-get install -y libgtk2.0*
#May be~ I had installed before 
```
#### Compile for Ubuntu
```shell
make
```
### Usage
```Shell
./main
```
Then type in url in text widget, you may see following (**Only support HTTP 1.x**):

![Screenshot from 2021-07-04 17-51-26](Screenshot%20from%202021-07-04%2017-51-26.png)

