# How to install the build script used on the OOP course

The `oop_build` script is already installed on MSYS2 on the KCL systems, and
included in the MSYS2 ZIP file provided for Windows users (link on the KEATS
website). You can invoke it simply by typing `oop_build` on the terminal.

It can easily be installed on any other Unix-like system by following these
instructions. If you're not familiar with this type of operation, we recommend
you copy/paste the following instructions into a terminal *exactly* as shown
below, in that order:

1. create the target folder if it doesn't already exist:
   ```
   mkdir -p ~/.local/bin
   ```
2. download the script to that target folder:
   ```
   curl https://raw.githubusercontent.com/jdtournier/simple_build/refs/heads/main/build > ~/.local/bin/oop_build
   ```
3. mark the script as executable:
   ```
   chmod a+x ~/.local/bin/oop_build
   ```
4. add the target folder to your shell startup script if that hasn't already
   been done:
   - if you use the `zsh` shell (default on macOS):
     ```
     grep -q '^export PATH=~/.local/bin/:' ~/.zshrc || echo 'export PATH=~/.local/bin/:"$PATH"' >> ~/.zshrc
     ```
   - if you use the `bash` shell (default on most other Unix systems):
     ```
     grep -q '^export PATH=~/.local/bin/:' ~/.bashrc || echo 'export PATH=~/.local/bin/:"$PATH"' >> ~/.bashrc
     ```

Feel free to modify these instructions to suit your needs if you're comfortable with this.


