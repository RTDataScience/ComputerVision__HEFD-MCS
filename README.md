# A High Efficiency Flame Detection Mobile Camera System (HEFD-MCS)
# 基於搖晃即時視訊之強韌式火焰偵測法 <font size=10pt>(Traditional Chinese)</font>

## Abstract
Two key issues of flame detection are high accuracy and low false alarm rate, and this study focuses the latter. In the past, static video from surveillance cameras was used to analyze and find the flames. However, these studies were conducted using the background method, which cannot process dynamic videos such as the video taken with a mobile phone. In order to achieve full automated flame detection for both static and dynamic video, two high-efficiency strategies are utilized in this study. Firstly, Feature Extraction: The Strong Sobel edge and the Flame Texture are established and then, the image edge is enhanced. The Flame Color Filter rules are helping filter the flame candidate regions. Secondly, High Performance Analysis Method: To filter flame or non-flame though by the motion vector method and the Fill rate, and then use groups to establish the contours of the flame. Our experimental results show that the results for static, dynamic (including shaky) and real-time video is 92.83% (TP), 9.76% (FP), 1.77% (FN).
### Keywords: Shaky Video, Intelligence Video Surveillance, Mobile Camera, Flame Detection, Real-Time.

## 摘要 <font size=9pt>(Traditional Chinese)</font>
火焰檢測的兩個關鍵問題是高精度和低誤報率，本研究主要關注後者。過去，監控攝影機的靜態視頻用於分析和偵測火焰。然而，這些研究是使用背景方法進行的，後者無法處理動態視頻，例如用手機拍攝的視頻。為了實現靜態和動態視頻的全自動火焰檢測，本研究採用了兩種高效策略。首先，特徵提取：建立強Sobel邊緣和火焰紋理，然後增強影像邊緣。火焰顏色過濾器規則有助於過濾火焰候選區域。其次，高性能分析方法：通過運動向量法和填充率過濾火焰或非火焰，然後使用群組建立火焰輪廓。我們的實驗結果表明，靜態，動態（包括抖動）和即時視頻的結果為92.83％（TP），9.76％（FP），1.77％（FN）。
### 關鍵字：抖動視頻，智慧型視頻監控，移動型攝像頭，火焰檢測，即時。<font size=8pt>(Traditional Chinese)</font>

### Related Site

<table border="1" width="100%">
	<tr>
		<td><b>Site</b></td>
		<td><b>Hyperlink<b></td>
	</tr>
	<tr>
		<td>YouTube</td>
		<td></td>
	</tr>
	<tr>
		<td>GitHub</td>
		<td><a href="https://github.com/laitaiyu/ComputerVision__HEFD-MCS">https://github.com/laitaiyu/ComputerVision__HEFD-MCS</a></td>
	</tr>
	<tr>
		<td>[1] A. Chenebert, T. P. Breckon, and A. Gaszczak, "A Non-Temporal Texture Driven Approach to Real-Time Fire Detection," In IEEE International Conference on Image Processing, Brussels, 2011, pp. 1741-1744.</td>
		<td><a href="https://ieeexplore.ieee.org/abstract/document/6115796" target="_blank">https://ieeexplore.ieee.org/abstract/document/6115796</a></td>
	</tr>
	<tr>
		<td>[5] B. Jiang, Y. Lu, X. Li, and L. Lin, "Towards A Solid Solution of Real-Time Fire and Flame Detection," Multimedia Tools and Applications, vol. 74, no. 3, Jul. 2014, pp. 689-705.</td>
		<td><a href="https://arxiv.org/abs/1502.00416" target="_blank">https://arxiv.org/abs/1502.00416</a></td>
	</tr>
	<tr>
		<td>[14] T. Çelik, H. Demirel, and H. Ozkaramanli, "Automatic Fire Detection in Video Sequences," in Proc. of the 14th European Signal Processing Conference, Florence, Italy, Sep. 4-8, 2006.</td>
		<td><a href="https://ieeexplore.ieee.org/document/7071275" target="_blank">https://ieeexplore.ieee.org/document/7071275</a></td>
	</tr>
	<tr>
		<td>[17] Y. Habiboglu, O. Günay, and A. E. Cetin, "Covariance Matrix-Based Fire and Flame Detection Method in Video," Machine Vision and Applications, vol. 23, no. 6, Sep. 2012, pp. 1103–1113.</td>
		<td><a href="https://link.springer.com/article/10.1007/s00138-011-0369-1" target="_blank">https://link.springer.com/article/10.1007/s00138-011-0369-1</a></td>
	</tr>
	<tr>
		<td>[18] Y. Qiang, B. Pei, and J. J. Zhao, "Forest Fire Image Intelligent Recognition Based on the Neural Network," Journal of Multimedia, vol. 9, no. 3, Mar. 2014, pp. 449-455.</td>
		<td><a href="https://www.semanticscholar.org/paper/Forest-Fire-Image-Intelligent-Recognition-based-on-Qiang-Pei/0817f553f66f46a32d7e5dc19d0656058b684cfc" target="_blank">https://www.semanticscholar.org/paper/Forest-Fire-Image-Intelligent-Recognition-based-on-Qiang-Pei</a></td>
	</tr>
</table>

### Tags
Computer Vision, Image Processing, Shaky Video, Static Video, Dynamic Video, Visual C++ 2017, DirectShow, 

### Authors
1. Lai Lin-Wen（賴琳紋），British Computer Society（英國電腦學會）
2. Lai Tai-Yu（賴岱佑），International Association of Computer Science and Information Technology（國際電腦科學與資訊科技協會），Email: <a href="mailto:Mr.LaiTaiyu@gmail.com">Mr.LaiTaiyu@gmail.com</a>，Blog: https://laitaiyu.blogspot.com/

### Development Environment 

<table border="1" width="100%">
	<tr>
		<td><b>Item</b></td>
		<td><b>Description<b></td>
	</tr>
	<tr>
		<td>Operating System（作業系統）</td>
		<td>Microsoft Windows 10 Pro Build 1809</td>
	</tr>
	<tr>
		<td>Integrated Development Environment（整合式開發環境）</td>
		<td>Microsoft Visual Studio 2017</td>
	</tr>
	<tr>
		<td>Programming Language</td>
		<td>Visual C++</td>
	</tr>
	<tr>
		<td>Library</td>
		<td>Windows 7.1 SDK, Microsoft DirectX SDK (June 2010), Microsoft DirectX 9.0 SDK (December 2004), DirectShow, ACTi IP-Camera SDK, iSAP NVR SDK</td>
	</tr>
</table>

### Version History

<table border="1" width="100%">
	<tr>
		<td><b>Version</b></td>
		<td><b>Description<b></td>
	</tr>
	<tr>
		<td>HEFD_MCS v1.0.2019.303<br/>
			<font size=8pt><i>Published: 3rd March 2019</i></font>
		</td>
		<td>Change the User Interface.</td>
	</tr>
	<tr>
		<td>HEFD_MCS v1.0.2018.1126<br/>
			<font size=8pt><i>Published: 26th November 2018</i></font>
		</td>
		<td>First Version.</td>
	</tr>
</table>

### Measurement

<table border="1" cellspacing="2" cellpadding="2" width="100%">
  <tr>
	<td width="7%" valign="top"><p>Video Type</p></td>
	<td width="46%" colspan="6"><p align="center">Static Video: 10 videos<br>
	  Video Source: A. E. Cetin [2], National Institute of Standards and Technology, Intelligent Media    Computing Laboratory, Sun Yat-Sen University</p></td>
	<td width="45%" colspan="6"><p align="center">Shaky (Dynamic) Video: 5 videos<br>
	  Video Source: Intelligent Media Computing    Laboratory, Sun Yat-Sen University</p></td>
  </tr>
  <tr>
	<td width="7%" valign="top"><p>Authors</p></td>
	<td width="7%" valign="top"><p>True Positive</p></td>
	<td width="7%" valign="top"><p>False Positive</p></td>
	<td width="7%" valign="top"><p>True Negative</p></td>
	<td width="7%" valign="top"><p>Precision</p></td>
	<td width="7%" valign="top"><p>Accuracy</p></td>
	<td width="7%" valign="top"><p>F-Measure e</p></td>
	<td width="7%" valign="top"><p>True Positive</p></td>
	<td width="7%" valign="top"><p>False Positive</p></td>
	<td width="7%" valign="top"><p>True Negative</p></td>
	<td width="7%" valign="top"><p>Precision</p></td>
	<td width="7%" valign="top"><p>Accuracy</p></td>
	<td width="7%" valign="top"><p>F-Measure e</p></td>
  </tr>
  <tr>
	<td width="7%" valign="top"><p>[1]</p></td>
	<td width="7%"><p align="right">732.3</p></td>
	<td width="7%"><p align="right">114.2</p></td>
	<td width="7%"><p align="right">114.2</p></td>
	<td width="7%"><p align="right">26.15</p></td>
	<td width="7%"><p align="right">27.2</p></td>
	<td width="7%"><p align="right">34.3</p></td>
	<td width="7%"><p align="right">1242.4</p></td>
	<td width="7%"><p align="right">754.4</p></td>
	<td width="7%"><p align="right">0</p></td>
	<td width="7%"><p align="right">69.19</p></td>
	<td width="7%"><p align="right">67.85</p></td>
	<td width="7%"><p align="right">80.02</p></td>
  </tr>
  <tr>
	<td width="7%" valign="top"><p>[14]</p></td>
	<td width="7%"><p align="right">720.1</p></td>
	<td width="7%"><p align="right">114.2</p></td>
	<td width="7%"><p align="right">114.2</p></td>
	<td width="7%"><p align="right">26.16</p></td>
	<td width="7%"><p align="right">27.04</p></td>
	<td width="7%"><p align="right">34.11</p></td>
	<td width="7%"><p align="right">1242.4</p></td>
	<td width="7%"><p align="right">576.6</p></td>
	<td width="7%"><p align="right">0</p></td>
	<td width="7%"><p align="right">73.56</p></td>
	<td width="7%"><p align="right">73.56</p></td>
	<td width="7%"><p align="right">83.09</p></td>
  </tr>
  <tr>
	<td width="7%" valign="top"><p>[18]</p></td>
	<td width="7%"><p align="right">1421.8</p></td>
	<td width="7%"><p align="right">174.3</p></td>
	<td width="7%"><p align="right">174.3</p></td>
	<td width="7%"><p align="right">63.6</p></td>
	<td width="7%"><p align="right">65.01</p></td>
	<td width="7%"><p align="right">72.62</p></td>
	<td width="7%"><p align="right">1242.4</p></td>
	<td width="7%"><p align="right">153.6</p></td>
	<td width="7%"><p align="right">0</p></td>
	<td width="7%"><p align="right">89.49</p></td>
	<td width="7%"><p align="right">89.49</p></td>
	<td width="7%"><p align="right">93.07</p></td>
  </tr>
  <tr>
	<td width="7%" valign="top"><p>HEFD-MCS</p></td>
	<td width="7%"><p align="right">1574.6</p></td>
	<td width="7%"><p align="right">238.55</p></td>
	<td width="7%"><p align="right">318.36</p></td>
	<td width="7%"><p align="right">90.6</p></td>
	<td width="7%"><p align="right">88.7</p></td>
	<td width="7%"><p align="right">90.5</p></td>
	<td width="7%"><p align="right">1240</p></td>
	<td width="7%"><p align="right">150.6</p></td>
	<td width="7%"><p align="right">0</p></td>
	<td width="7%"><p align="right">89.89</p></td>
	<td width="7%"><p align="right">89.55</p></td>
	<td width="7%"><p align="right">93.11</p></td>
  </tr>
</table>

***
<table border="1" cellspacing="2" cellpadding="2" width="100%">
	<tr>
		<td width="7%" valign="top"><p>&nbsp;</p></td>
		<td width="30%" colspan="4"><p align="center">Video Type</p></td>
		<td width="30%" colspan="4"><p align="center">Static Video: 2 videos <br>
		  Video Source: A. E. Cetin [2] , UltimateChase.com </p></td>
	</tr>
	<tr>
		<td width="7%" valign="top"><p>Authors</p></td>
		<td width="7%" valign="top"><p>Title</p></td>
		<td width="8%" valign="top"><p>Frame Per Second (FPS)</p></td>
		<td width="9%" valign="top"><p>Resolution<br>
		  (Pixel)</p></td>
		<td width="5%" valign="top"><p>Total Frames</p></td>
		<td width="7%" valign="top"><p>True Positive</p></td>
		<td width="7%" valign="top"><p>False Positive</p></td>
		<td width="7%" valign="top"><p>False Negative</p></td>
		<td width="8%" valign="top"><p>Average Time Per Frame</p></td>
	</tr>
	<tr>
		<td width="7%" valign="top"><p>[5] </p></td>
		<td width="7%" valign="top"><p>Forest    fire 2</p></td>
		<td width="8%" valign="top"><p align="center">15</p></td>
		<td width="9%" valign="top"><p align="center">400×256</p></td>
		<td width="5%" valign="top"><p align="center">178</p></td>
		<td width="7%" valign="top"><p align="right">24.7% </p></td>
		<td width="7%" valign="top"><p align="right">No provided</p></td>
		<td width="7%" valign="top"><p align="right">No provided</p></td>
		<td width="8%" valign="top"><p align="right">2 Second</p></td>
	</tr>
	<tr>
		<td width="7%" valign="top"><p>[17] </p></td>
		<td width="7%" valign="top"><p>Pos Video    11</p></td>
		<td width="8%" valign="top"><p align="center">30</p></td>
		<td width="9%" valign="top"><p align="center">352×288</p></td>
		<td width="5%" valign="top"><p align="center">505</p></td>
		<td width="7%" valign="top"><p align="right">19.7% </p></td>
		<td width="7%" valign="top"><p align="right">No provided</p></td>
		<td width="7%" valign="top"><p align="right">No provided</p></td>
		<td width="8%" valign="top"><p align="right">‪50 Milli-Second </p></td>
	</tr>
	<tr>
		<td width="7%" rowspan="4" valign="top"><p>HEFD-MCS</p></td>
		<td width="7%" valign="top"><p>Forest    fire 2</p></td>
		<td width="8%" valign="top"><p align="center">15</p></td>
		<td width="9%" valign="top"><p align="center">400×256</p></td>
		<td width="5%" valign="top"><p align="center">178</p></td>
		<td width="7%" valign="top"><p align="right">100%</p></td>
		<td width="7%" valign="top"><p align="right">0%</p></td>
		<td width="7%" valign="top"><p align="right">0%</p></td>
		<td width="8%" valign="top"><p align="right">80 Milli-Second </p></td>
	</tr>
	<tr>
		<td width="7%" valign="top"><p>Pos Video    11</p></td>
		<td width="8%" valign="top"><p align="center">30</p></td>
		<td width="9%" valign="top"><p align="center">352×288</p></td>
		<td width="5%" valign="top"><p align="center">505</p></td>
		<td width="7%" valign="top"><p align="right">78.2%</p></td>
		<td width="7%" valign="top"><p align="right">8.7%</p></td>
		<td width="7%" valign="top"><p align="right">0%</p></td>
		<td width="8%" valign="top"><p align="right">40 Milli-Second </p></td>
	</tr>
	<tr>
		<td width="30%" colspan="4"><p align="center">Video Type</p></td>
		<td width="30%" colspan="4"><p align="center">The Negative Sample of the Static Video: 5    videos<br>
		  Video Source: Intelligent Media Computing    Laboratory, Sun Yat-Sen University</p></td>
	</tr>
	<tr>
		<td width="30%" colspan="4" valign="top"><p align="center">5 Sample Videos</p></td>
		<td width="7%" valign="top"><p align="right">98%</p></td>
		<td width="7%" valign="top"><p align="right">2%</p></td>
		<td width="7%" valign="top"><p align="right">0%</p></td>
		<td width="8%" valign="top"><p align="right">40 Milli-Second </p></td>
	</tr>
	<tr>
		<td width="7%" valign="top"><p>[1] </p></td>
		<td width="30%" colspan="4" valign="top"><p align="center">5 Sample Videos</p></td>
		<td width="7%" valign="top"><p align="right">0%</p></td>
		<td width="7%" valign="top"><p align="right">100%</p></td>
		<td width="7%" valign="top"><p align="right">0%</p></td>
		<td width="8%" valign="top"><p align="right">30 Milli-Second </p></td>
	</tr>
	<tr>
		<td width="7%" valign="top"><p>[14] </p></td>
		<td width="30%" colspan="4" valign="top"><p align="center">5 Sample Videos</p></td>
		<td width="7%" valign="top"><p align="right">0%</p></td>
		<td width="7%" valign="top"><p align="right">100%</p></td>
		<td width="7%" valign="top"><p align="right">0%</p></td>
		<td width="8%" valign="top"><p align="right">30 Milli-Second </p></td>
	</tr>
	<tr>
		<td width="7%" valign="top"><p>[18] </p></td>
		<td width="30%" colspan="4" valign="top"><p align="center">5 Sample Videos</p></td>
		<td width="7%" valign="top"><p align="right">67%</p></td>
		<td width="7%" valign="top"><p align="right">33%</p></td>
		<td width="7%" valign="top"><p align="right">0%</p></td>
		<td width="8%" valign="top"><p align="right">30 Milli-Second </p></td>
	</tr>
</table>

***
<table border="1" cellspacing="0" cellpadding="0" width="100%">
	<tr>
		<td width="20%" valign="top"><p>&nbsp;</p></td>
		<td width="79%" colspan="4"><p align="center">Shaky (Dynamic) Video: 1 video<br>
		  Video Source: UltimateChase.com</p></td>
	</tr>
	<tr>
		<td width="20%" valign="top"><p>Authors</p></td>
		<td width="18%" valign="top"><p>True Positive</p></td>
		<td width="18%" valign="top"><p>False Positive</p></td>
		<td width="18%" valign="top"><p>False Negative</p></td>
		<td width="22%" valign="top"><p>Average Time Per Frame</p></td>
	</tr>
	<tr>
		<td width="20%" valign="top"><p>[5]</p></td>
		<td width="79%" colspan="4" valign="top"><p>The study [5] uses a background model. Therefore, it is not suitable the shaky video.</p></td>
	</tr>
	<tr>
		<td width="20%" valign="top"><p>[17]</p></td>
		<td width="18%" valign="top"><p align="right">83%</p></td>
		<td width="18%" valign="top"><p align="right">No provided</p></td>
		<td width="18%" valign="top"><p align="right">No provided</p></td>
		<td width="22%" valign="top"><p align="right">50 Milli-Second</p></td>
	</tr>
	<tr>
		<td width="20%" rowspan="2" valign="top"><p>HEFD-MCS</p></td>
		<td width="79%" colspan="4" valign="top"><p align="center">Shaky (Dynamic) Video: 5 videos<br>
		  Video Source: Intelligent Media Computing    Laboratory, Sun Yat-Sen University</p></td>
	</tr>
	<tr>
		<td width="18%" valign="top"><p align="right">90%</p></td>
		<td width="18%" valign="top"><p align="right">12%</p></td>
		<td width="18%" valign="top"><p align="right">0.19%</p></td>
		<td width="22%" valign="top"><p align="right">150 Milli-Second</p></td>
	</tr>
	<tr>
		<td width="20%" valign="top"><p>[1][14][18]</p></td>
		<td width="79%" colspan="4" valign="Top">
			<p>
			These studies [1][14][18] use their background model. Therefore, they are not suitable the shaky video.
			</p>
		</td>
	</tr>
</table>

***
<table width="100%" style="background-color:#EEEEEE;">
	<tr>
		<td align="center">Copyright &copy; 2019 Lai Lin-Wen and Lai Tai-Yu.</td>
	</tr>
	<tr>
		<td align="right"><font size="8pt"><i>Last Update: 3rd March, 2019</i></font></td>
	</tr>
</table>