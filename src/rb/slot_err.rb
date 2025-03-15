# This script is to run when abnormal program termination happens.
# Before building openblink-demo-m5, this file should be byte-compiled by yourself.
# $ mrbc -B slotsleep -o slotsleep.h slotsleep.rb

RED = [255, 0, 0]
BLACK = [0, 0, 0]

# do SOS in LED

def showS
  3.times do 
    LED.set(RED)
    sleep 0.1
    LED.set(BLACK)
    sleep 0.1
  end
end
def showO
  3.times do  
    LED.set(RED)
    sleep 0.3
    LED.set(BLACK)
    sleep 0.1
  end
end


while true do 
  puts "press BtnA or update via Blink to escape this loop"
  showS
  sleep 0.1
  showO
  sleep 0.1
  showS
  sleep 2
  break if Blink.req_reload? or Input.pressed?
end
