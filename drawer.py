
import matplotlib.pyplot as plt
fig, ax = plt.subplots()
ax.set_xlim([0,20])
ax.set_ylim([0,20])
fileline = open("lines.txt",'w')
fileline.truncate()
filerect = open("rect.txt",'w')
filerect.truncate()
class LineDrawer(object):
    lines = []
    
    def draw_line(self, startx,starty):
        ax = plt.gca()


        
        xy = plt.ginput(1)
        y1 = xy[0][0]
        y2 = xy[0][1]
        x = [startx,y1]
        y = [starty,y2]
        print(x)
        print(y)
        for coord in x:
            print(coord)
            fileline.write(str(coord)+' ')
        for coord in y:
            print(coord)
            fileline.write(str(coord)+' ')
        fileline.write('\n')
        fileline.flush()
        line = plt.plot(x,y)
        ax.figure.canvas.draw()

        self.lines.append(line)

def onclick(event):
    
    if event.dblclick:
        if event.button == 1:
            ld = LineDrawer()
            ld.draw_line(event.xdata,event.ydata) # here you click on the plot
    elif event.button == 2:
        rect =plt.Rectangle(
                    (event.xdata, event.ydata),
                        5,5,linewidth=1, edgecolor="r", facecolor= "none")
        bottomleftx = event.xdata
        bottomlefty = event.ydata
        toprightx = event.xdata + 5
        toprighty = event.ydata + 5
        filerect.write(str(bottomleftx) + ' ' + str(bottomlefty) + ' ' + str(toprightx)
         +    ' ' + str(toprighty))
        ax.add_patch(rect)
        filerect.flush()
        
connection_id = fig.canvas.mpl_connect('button_press_event', onclick)


plt.tight_layout()

plt.show()