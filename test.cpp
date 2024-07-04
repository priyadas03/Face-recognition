//Run this code on visual studio 

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    // Load the video capture
    VideoCapture video(0);
    if (!video.isOpened()) {
        cerr << "Error: Could not open the video capture" << endl;
        return -1;
    }

    // Load the face detection model
    CascadeClassifier facedetect;
    if (!facedetect.load("haarcascade_frontalface_default.xml")) {
        cerr << "Error: Could not load face detector model" << endl;
        return -1;
    }

    Mat img;
    while (true) {
        // Capture the frame
        video.read(img);
        if (img.empty()) {
            cerr << "Error: Could not read frame" << endl;
            break;
        }

        vector<Rect> faces;
        // Detect faces
        facedetect.detectMultiScale(img, faces, 1.3, 5);

        // Print the number of faces detected
        cout << faces.size() << endl;

        // Draw rectangles around the faces
        for (int i = 0; i < faces.size(); i++) {
            rectangle(img, faces[i].tl(), faces[i].br(), Scalar(50, 50, 255), 3);
            rectangle(img, Point(0, 0), Point(250, 70), Scalar(50, 50, 255), FILLED);
            putText(img, to_string(faces.size()) + " Face(s) Found", Point(10, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1);
        }

        // Display the frame
        imshow("Frame", img);
        // Wait for a key press; if a key is pressed, break the loop
        if (waitKey(1) >= 0) break;
    }

    return 0;
}
