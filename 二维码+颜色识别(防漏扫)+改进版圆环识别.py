import sensor, image, time

from pyb import UART  #串口
uart = UART(3, 9600)  #串口实体化
uart_receive = ""         #串口接收存储

sensor.reset() # 初始化摄像头
sensor.set_pixformat(sensor.RGB565) # 格式为 RGB565.
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(10) # 跳过10帧，使新设置生效
#sensor.set_auto_whitebal(False)               # 白平衡
#sensor.set_auto_gain(False)                   # 自动增益

color_l=[0 for i in range(6)]  #存储颜色的lab值
color_a=[0 for i in range(6)]
color_b=[0 for i in range(6)]

color=["0" for i in range(6)]  #存储位置颜色

place=""   #存储位置信息

ROI=[(0,0,0,0) for i in range(6)]

ROI[0]=(38,70,20,20)
ROI[1]=(148,70,20,20)
ROI[2]=(260,75,20,20)
ROI[3]=(45,155,20,20)
ROI[4]=(150,155,20,20)
ROI[5]=(260,160,20,20)

c_x=0
c_y=0

def draw():
    for x in range(6):
        img.draw_rectangle(ROI[x])

def print_lab():
    print("color0:",color_l[0],color_a[0],color_b[0])
    print("color1:",color_l[1],color_a[1],color_b[1])
    print("color2:",color_l[2],color_a[2],color_b[2])
    print("color3:",color_l[3],color_a[3],color_b[3])
    print("color4:",color_l[4],color_a[4],color_b[4])
    print("color5:",color_l[5],color_a[5],color_b[5])

while(True):
    img = sensor.snapshot()         # 截图
    #img.lens_corr(1.8)          #抗鱼眼
    draw()
    if uart.any():
        a = uart.readline().decode()
        uart_receive = a
        print(uart_receive)
    while (uart_receive=="1"):
        img = sensor.snapshot()         # 截图
        #img.lens_corr(1.8)          #抗鱼眼
        for code in img.find_qrcodes():
            Mission = code.payload()+'\n'
            print("Mission:",Mission)
            if len(Mission)==8:
                uart.write(Mission)
                uart_receive="0"

    while (uart_receive=="2"):
        img = sensor.snapshot()         # 截图
        #img.lens_corr(1.8)          #抗鱼眼
        for x in range(6):
            statistics=img.get_statistics(roi=ROI[x])
            color_l[x]=statistics.l_mode()
            color_a[x]=statistics.a_mode()
            color_b[x]=statistics.b_mode()
            if color_l[x]>24 and color_l[x]<66 and color_a[x]>12 and color_a[x]<109 and color_b[x]>-29 and color_b[x]<56:
                color[x]="1"
                #(24, 66, 12, 109, -29, 56)
            if color_l[x]>8 and color_l[x]<69 and color_a[x]>-88 and color_a[x]<-14 and color_b[x]>-34 and color_b[x]<85:
                color[x]="2"
                #(8, 69, -88, -14, -34, 85)
            if color_l[x]>8 and color_l[x]<57 and color_a[x]>-31 and color_a[x]<63 and color_b[x]>-113 and color_b[x]<-5:
                color[x]="3"
                #(8, 57, -31, 63, -113, -5)
        #print_lab()

        if color[0]=="0" and color[1]!="0" and color[2]!="0":
            color[0]=str(6-int(color[1])-int(color[2]))
        if color[1]=="0" and color[0]!="0" and color[2]!="0":
            color[1]=str(6-int(color[0])-int(color[2]))
        if color[2]=="0" and color[0]!="0" and color[1]!="0":
            color[2]=str(6-int(color[0])-int(color[1]))
        if color[3]=="0" and color[4]!="0" and color[5]!="0":
            color[3]=str(6-int(color[4])-int(color[5]))
        if color[4]=="0" and color[3]!="0" and color[5]!="0":
            color[4]=str(6-int(color[3])-int(color[5]))
        if color[5]=="0" and color[3]!="0" and color[4]!="0":
            color[5]=str(6-int(color[3])-int(color[4]))

        for x in range(6):
            place+=str(color[x])
        place = place+'\n'
        if len(place)==7:
            print("place:",place)
            uart.write(str(place))
            place=""
            for x in range(6):
                color[x]="0"
            uart_receive="0"

    while (uart_receive=="3"):
        sensor.set_framesize(sensor.QQVGA)
        sensor.skip_frames(10)
        for x in range(10):
            img = sensor.snapshot()         # 截图
            #img.lens_corr(1.8)          #抗鱼眼
            for c in img.find_circles(threshold = 3500, x_margin = 10, y_margin = 10, r_margin = 10,r_min = 2, r_max = 100, r_step = 2):
                c_x=c.x()
                c_y=c.y()
            if c_x!=0 or c_y!=0:
                break
        print(c_x,c_y)
        data = bytearray([c_x,c_y])
        uart.write(data)
        c_x=0
        c_y=0
        uart_receive="0"







