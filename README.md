### Vision OS
Tired of complex af systems?
Believe that it's all about simple and beatiful stuff?
Minimalism in action!!!

### What is Vision?
Basically, start write this os for own purpose and for learning.
After a while take too serious with that stuff.
### Run qemu with kernel to wait for gdb remote:
- qemu-system-arm -M lm3s811evb -kernel <kernel> -nographic -s -S 

### Run gdb remote
- 1 Setup architecture for armv7
- 2 Run: target remote localhost:1234
