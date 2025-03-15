white=0xffff
blue=0x001f
green=0x07e0
purple=0xf81f
red=0xf800
cyan=0x07ff
yellow=0xffe0
black=0x0000
gray=0x8410
darkgray=0x4208
lightgray=0xc618

xscale=1.5
yscale=1.5
xoffset=0
yoffset=50

def dot(x,y,c)
  Display.draw_line(x.to_i,y.to_i,x.to_i,y.to_i,c)
end

Display.clear
while true do
  d=Array.new(160,100)

  dr=3.141592/180
  (-30..30).each do |by|
    (-30..30).each do |bx|
      x=bx*6; y=by*6
      r=dr*Math.sqrt(x*x+y*y)
      z=100*Math.cos(r) - 30*Math.cos(3*r)
      sx=(80+x/3-y/6).to_i
      sy=(40-y/6-z/4).to_i
      if sx>=0 && x<160 then
        if d[sx]>sy then
          zz=((z+100)*0.035).to_i+1
          if [1,2,5,7].include?(zz) then
            dot(xscale*sx+xoffset,yscale*sy+yoffset,white)
          elsif  [2,3].include?(zz) or zz>=6 then
            dot(xscale*sx+xoffset,yscale*sy+yoffset,green)
          elsif zz>=4 then
            dot(xscale*sx+xoffset,yscale*sy+yoffset,purple)
          end
          d[sx]=sy
        end
      end
    end
  end
  sleep 1
  break if Blink.req_reload?
  Display.clear
end