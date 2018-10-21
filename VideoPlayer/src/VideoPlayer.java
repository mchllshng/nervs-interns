import java.awt.Desktop;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class VideoPlayer {
	
	private File textFile;
	private File durationFile;
	private Scanner in;
	private ArrayList<Integer> videoList;
	private ArrayList<Integer> durationList;
	
	public VideoPlayer(String fileName,  String durationFileName) throws IOException, InterruptedException {
		
		this.textFile = new File(fileName);
		this.durationFile = new File(durationFileName);
		readInFile(this.textFile);
		readInDurationFile(this.durationFile);
		videoFeed();
	}
	
	public void readInFile(File textFile) throws FileNotFoundException {
		
		this.videoList = new ArrayList<Integer>();

		try {
			this.in = new Scanner(textFile);
			
			while (in.hasNextLine()) {
				
				this.videoList.add(in.nextInt());
				if (in.hasNextLine()) {
					in.nextLine();
				}
			}
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} finally {
			in.close();
		}
		//test();
	}
	
	public void readInDurationFile(File durationFile) {
		
		this.durationList = new ArrayList<Integer>();

		try {
			this.in = new Scanner(durationFile);
			
			while (in.hasNextLine()) {
				
				int durationConversionToMilli = (in.nextInt() + 1) * 1000;
				this.durationList.add(durationConversionToMilli);
				if (in.hasNextLine()) {
					in.nextLine();
				}
			}
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} finally {
			in.close();
		}
	}
	
	public void videoFeed() throws IOException, InterruptedException {
		int count = 0;
		
		while (this.videoList.size() > count) {
			
			int videoNum = this.videoList.get(count);
			playVideo(videoNum);
			Thread.sleep(this.durationList.get(videoNum - 1));
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
		
		new VideoPlayer("file.txt", "duration.txt");
		
	}
} 