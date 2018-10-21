import java.awt.Desktop;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class VideoPlayer {
	
	private File textFile;
	private Scanner in;
	private ArrayList<Integer> videoList;
	private ArrayList<Integer> durationList;
	
	public VideoPlayer(String fileName) throws IOException, InterruptedException {
		
		this.textFile = new File(fileName);
		readInFile(this.textFile);
		videoFeed();
	}
	
	public void readInFile(File textFile) throws FileNotFoundException {
		
		this.videoList = new ArrayList<Integer>();
		this.durationList = new ArrayList<Integer>();

		try {
			this.in = new Scanner(textFile);
			
			while (in.hasNextLine()) {
				
				this.videoList.add(in.nextInt());
				int durationConversiontoMilli = (in.nextInt() + 1) * 1000; //the 1 is a time cushion.
				this.durationList.add(durationConversiontoMilli);
				if (in.hasNextLine()) {
					in.nextLine();
				}
			}
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		//test();
	}
	
	public void videoFeed() throws IOException, InterruptedException {
		int count = 0;
		
		while (this.videoList.size() > count) {
			playVideo(this.videoList.get(count));
			Thread.sleep(this.durationList.get(count));
			count++;
		}
	}
	
	private void playVideo(int videoNum) throws IOException, InterruptedException {

		try {
			switch (videoNum) {
			case 1:  Desktop.getDesktop().open(new File("video1.mp4"));
			//the "video1" name shows on screen so we can use it as a caption/title of the video.
					 break;
            case 2:  Desktop.getDesktop().open(new File("video2.mp4"));
            		 break;
            case 3:  Desktop.getDesktop().open(new File("video3.mp4"));
            		 break;
            case 4:  Desktop.getDesktop().open(new File("video4.mp4"));
                     break;
            default: break;
			}
        } catch (FileNotFoundException e) {
        	e.printStackTrace();
        }

	}
	
	private void test() {
		
		for(int i = 0; i < this.videoList.size(); i++) {
			System.out.println(this.videoList.get(i));
		}
	}

	public static void main(String[] args) throws IOException, InterruptedException {
		
		new VideoPlayer("file.txt");
		
	}
} 