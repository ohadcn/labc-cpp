import java.awt.*;

import javax.swing.JFrame;

import java.io.*;
import java.util.Scanner;

public class Drawing extends JFrame {

	private static final long serialVersionUID = 1L;
	
	private static final Color colors[]={Color.BLUE,Color.GREEN,Color.BLACK,Color.ORANGE,Color.YELLOW};
	
	private static final int SIZE=600;

	private static final int FACTOR=400;

	public static void main(String[] args) {
		int i=0;
		Drawing f = new Drawing();
		f.setTitle("draw it!");
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setBounds(0, 0, SIZE, SIZE);
		f.setVisible(true);
		Graphics e = f.getGraphics();
		for(String s:args){
			int[][] o=readFromFile(s);
			e.setColor(colors[i++]);
			e.drawPolyline(o[0], o[1], o[2][0]);
		}
	}
	
	private static int[][] readFromFile(String name) {
		int x[]=new int[1000],y[]=new int[1000];
		int i=0;
		try {
			File f=new File(name);
			Scanner s= new Scanner(f);
			if(s.hasNext("result"))
				s.nextLine();
			
			while(s.hasNext()){
				String t=s.nextLine();
				String k[]=t.split(",");
				x[i]=Integer.parseInt(k[0])/FACTOR+SIZE/2;
				y[i++]=Integer.parseInt(k[1])/FACTOR+SIZE/2;
			}
			s.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		int r[][]={x,y,{i}};
		return r;
	}

	@Override
    public void paint(Graphics g) {
	}
}
