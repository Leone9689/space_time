#include "keyslice_tracker.h"

KeySlice::KeySlice()
{
 findKeySlice(5,750);
}
void KeySlice::findKeySlice(int d,int pixelThreshold)  
{
  
  //std::ifstream in("/home/leone/Documents/bechmark/rgbd_dataset_freiburg3_long_office_household/rgb.txt");  
  std::ifstream in("/home/leone/Documents/bechmark/rgbd_dataset_freiburg1_360/rgb.txt");
  std::string path = "/home/leone/Documents/bechmark/rgbd_dataset_freiburg1_360/";  
  // std::ifstream in("/home/leone/data/rgbd_dataset_freiburg1_desk/rgb.txt");
  // ofstream out("/rgbd_dataset_freiburg3_long_office_household/2.txt");
  //std::string path = "/home/leone/Documents/bechmark/rgbd_dataset_freiburg3_long_office_household/";  
  // std::string path = "rgbd_dataset_freiburg1_desk/"; 
  std::string filename;  
  std::string line;  
  float junkstamp; 
  std::string rgbname;
  std::vector <std::string> rgbnames;  
  cv::Mat bluePixel,greenPixel,redPixel;
  std::map <int,std::map <int,ushort> > bluePixels;  
  std::map <int,std::map <int,ushort> > greenPixels;
  std::map <int,std::map <int,ushort> > redPixels;
  if(in) // 有该文件  
    {  
     while (getline (in, line)) // line中不包括每行的换行符  
      {   
       std::stringstream stream(line);
       stream >> junkstamp;  
       stream >> rgbname;
       
       rgbnames.push_back(path+rgbname);  
      }
    } 
  else // 没有该文件  
    {  
      std::cout <<"no such file" <<std::endl;  
    }   
    
  //bluePixels.create(480,rgbnames.size(),CV_16UC1);
  std::vector <ushort> keyId;
  //cv::Mat greenPixels(480,rgbnames.size(),CV_16UC1);
  //cv::Mat redPixels(480,rgbnames.size(),CV_16UC1);
  int keyFrame=0;
  //cv::Mat bluePixels(480,1000,CV_16UC1);
  
  int cnt1=0,cnt2=0,cnt3=0;
  int pixelChange=0,pixelChange1=0,pixelChange2=0,pixelChange3=0;

  for(std::vector<int>::size_type ix =0; ix != rgbnames.size(); ++ix)
    { 
      std:: cout<<"Now rgb["<<ix<< "]is: "<<rgbnames[ix]<<std::endl;  
      cv::Mat rgb,blue,green,red;
      std::vector <cv::Mat > mv;
      rgb = cv::imread(rgbnames[ix]);
     // std::cout<<rgb.type()<<std::endl ;
     /* if(rgb.type()==CV_8UC3)
      {
         std::cout<<"rgb is"<<rgb.type()<<std::endl ;
      }
     // rgb = cv::imread("rgbd_dataset_freiburg3_long_office_household/rgb/1341847980.754743.png");
    */ 
      if(rgb.empty())
      {  
        std::cout<<"Can not load image"<<std::endl ;
        return ; 
      }  
      std::cout<<"rgb type: "<<rgb.type()<<std::endl;
      cv::split(rgb,mv);
      blue = mv[0];
      green = mv[1];
      red = mv[2];
      for (int n=0; n <blue.rows; n++)
      {                        
        // 获取深度图中(m,n)处的值
          bluePixels[ix][n]= blue.at<ushort>(n,320);
          greenPixels[ix][n]= green.at<ushort>(n,320);
          redPixels[ix][n]= red.at<ushort>(n,320);    

        //    bluePixels.at<ushort>(n,ix) = blue.at<ushort>(n,320);
        //  greenPixels.at<ushort>(n,ix) = green.at<ushort>(n,320);
        //  redPixels.at<ushort>(n,ix) = red.at<ushort>(n,320);
         // std::cout<<redPixels.at<ushort>(n,ix)<<","<<greenPixels.at<ushort>(n,ix)<<","<< bluePixels.at<ushort>(n,ix)<<std::endl ;
       // std::cout<<bluePixels[ix][n]<<","<< greenPixels[ix][n]<<","<< redPixels[ix][n]<<std::endl;
      } 
      //std::cout<<bluePixels.at<ushort>(240,ix)<<","<<greenPixels.at<ushort>(240,ix)<<","<< redPixels.at<ushort>(240,ix)<<std::endl;
      // int d=4;//-5~5范围的像素点
     // int cnt1=0,cnt2=0,cnt3=0;
     // int pixelChange1=0,pixelChange2=0,pixelChange3=0;
      if(ix==0)
        continue;
      else
      {
        for(int j=0+d;j<blue.rows-d;j++)
        {
          for(int i=d;i>=-d;i--)
          {
           // int a =abs(bluePixels.at<ushort>(j,ix)- bluePixels.at<ushort>(j+i,ix-1));
            int a = abs(bluePixels[ix][j]- bluePixels[ix-1][j+i]);
            int b = abs(greenPixels[ix][j]- greenPixels[ix-1][j+i]);
            int c = abs(redPixels[ix][j]- redPixels[ix-1][j+i]);    

            // int b =abs(greenPixels.at<ushort>(j,ix)- greenPixels.at<ushort>(j+i,ix-1));
           // int c =abs(redPixels.at<ushort>(j,ix)- redPixels.at<ushort>(j+i,ix-1));
          //  std::cout<<"a: "<<a<<",b: "<<b<<",c: "<<c<<std::endl;
            if(a>=1000)
             cnt1++;
            if(b>=1000)
             cnt2++;
            if(c>=1000)
             cnt3++;
          }
          //std::cout<<"cnt1:"<<cnt1<<"cnt2: "<<cnt2<<"cnt3: "<<cnt3<<std::endl; 
          if(cnt1==(2*d+1))
            pixelChange1++;
          if(cnt2==(2*d+1))
            pixelChange2++;
          if(cnt3==(2*d+1))
            pixelChange3++;
          cnt1=0;cnt2=0;cnt3=0;
        }
        //std::cout<<"blue pixel change: "<<pixelChange1<<",green pixel change: "<<pixelChange2<<",red pixel change: "<<pixelChange3<<std::endl;
        pixelChange = pixelChange1+pixelChange2+pixelChange3;
        if(pixelChange >=pixelThreshold)
        {
         // bluekeyPixels.push_back(bluePixels.at<ushort>(j,ix));
         // pixelChange = 0;
          keyFrame++;
          keyId.push_back(ix) ;
          rgbImage.push_back(rgb); 
        }
          pixelChange = 0;
      }
      pixelChange1=0;pixelChange2=0;pixelChange3=0;
    }
 keySlice.create(480,keyFrame,CV_16UC1);
/* for(std::vector<int>::size_type ix =0; ix != keyId.size(); ++ix)
   for(int n=0;n<480;n++)
 {
  keySlice.at<ushort>(n,ix)= redPixels.at<ushort>(n,keyId[ix]);
 }
 */
 std::cout<<"rgb frame is: "<<rgbnames.size()<<std::endl;
 std::cout<<"key frame is: "<<keyFrame<<std::endl; 
// std::cout<<redPixels.rows<<std::endl ; 
// std::cout<<redPixels.cols<<std::endl ; 
// cv::namedWindow("R", 1);
// cv::namedWindow("G", 1);
/* cv::namedWindow("B", 1);
 cv::namedWindow("Key slice");

// cv::imshow("R", redPixels); 
// cv::imshow("G", greenPixels);      
 cv::imshow("B", redPixels);
 cv::imshow("Key slice",keySlice);
  //此函数等待按键，按键盘任意键就返回
*/
  cv::waitKey();

}
