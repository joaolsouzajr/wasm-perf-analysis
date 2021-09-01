/*
Copyright 2021, Joao Lourenco Souza Junior, all rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "detectorsz/dzapp.hpp"
#include <string.h>
#include <dirent.h>
#include <algorithm>


namespace dzapp {
    void configureParams(int argc, char **argv) {
        int resolutionParam = ScaleResolution::SMALL;
        if (argc > 4) {
            datasetName = argv[1];
            datasetPath = argv[2];
            resolutionParam = stoi(argv[3]);
            workloadSelected =
                    stoi(argv[4]) == 0 ? Workload::FACE_DETECT : Workload::FACE_EYES_DETECT;
        } else {
            cout << "Invalid params!" << endl;
            cout << "Usage example: .\\detectorsz_app.exe DATASET_7"
                 << " .\\dataset\\DATASET_1 0 0" << endl;
            return;
        }
        if (ScaleResolution::SMALL == resolutionParam) {
            scaleResoution = SMALL_RESOLUTION;
            resolutionLabel = "SMALL";
        } else if (ScaleResolution::MEDIUM == resolutionParam) {
            scaleResoution = MEDIUM_RESOLUTION;
            resolutionLabel = "MEDIUM";
        } else if (ScaleResolution::LARGE == resolutionParam) {
            scaleResoution = LARGE_RESOLUTION;
            resolutionLabel = "LARGE";
        } else {
            cout << "Resolution to scale not supported" << endl;
            return;
        }
        cout << datasetName << " WASM - Tests" << endl;
    }

    void getFilenames(const string &dirName, vector<string> &fileNames) {
        DIR *dir;
        string name;
        struct dirent *ent;
        if ((dir = opendir(dirName.c_str())) != NULL) {
            /* print all the files and directories within directory */
            while ((ent = readdir(dir)) != NULL) {
                if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
                    fileNames.push_back(ent->d_name);
                }

            }
            closedir(dir);
        }
    }

    void report(FaceDetect &faceDetect) {
        // Report logs in a CSV file.
        ofstream logFile;
        string workloadName = workloadSelected == Workload::FACE_DETECT
                              ? FACE_DETECT_NAME
                              : FACE_EYES_DETECT_NAME;
        //string system = "WINDOWS_10_WIN32";
        string system = "LINUX";
        string reportName = "LOG_" + workloadName + "_" + datasetName + "_" +
                            resolutionLabel + "_" + system;
        logFile.open(reportName + ".csv");
        string head = ",system,resolution_label";
        string columns = "," + system + "," + resolutionLabel;
        logFile << faceDetect.logsToStringAndAddCommon(head, columns) << endl;
        cout << "Report:" << reportName << ".csv" << endl;
        cout << "Workload: " << workloadName << endl;
        cout << "Dataset: " << datasetName << endl;
        cout << "System: " << system << endl;
        cout << "Total of frames : " << frameCount << endl;
        cout << "Total of frames processeds: " << frameIndex << endl;
        cout << "Total time of test: " << totalTime << endl;
        logFile.close();
        logFile.open("META_" + reportName + ".csv");
        logFile << "workload,dataset,resolution,system,total_frames,"
                   "total_frames_processeds,test_total_time_ms,log_file"
                << endl;
        logFile << workloadName << "," << datasetName << "," << resolutionLabel << ","
                << system << "," << frameCount << "," << frameIndex << ","
                << totalTime << "," << reportName << ".csv" << endl;
        cout << workloadName << "," << datasetName << "," << resolutionLabel << ","
             << system << "," << frameCount << "," << frameIndex << "," << totalTime
             << "," << reportName << ".csv" << endl;
        logFile.close();
    }

    void processImages() {
        FaceDetect faceDetect(dzapp::datasetName);

        vector<string> fileNames;
        std::vector<cv::Mat> my_images;

        getFilenames(dzapp::datasetPath, fileNames);
        std::sort(fileNames.begin(), fileNames.end());

        for (int i = 0; i < fileNames.size(); i++) {
            my_images.push_back(cv::imread(dzapp::datasetPath + "/" + fileNames.at(i)));
        }
        frameCount = my_images.size();
        auto start = high_resolution_clock::now();
        for (int i = 0; i < my_images.size(); i++) {
            //cout << fileNames.at(i) << endl;

            MatAdapter matWSrc{my_images.at(i).rows, my_images.at(i).cols, my_images.at(i).type()};
            matWSrc.matImg.data = my_images.at(i).data;

            auto t0 = high_resolution_clock::now();

            if (Workload::FACE_EYES_DETECT == workloadSelected) {
                // Detect faces and eyes with log time
                faceDetect.faceAndEyesDetectWithLog(matWSrc);
            } else {
                // Detect faces with log time
                faceDetect.faceDetectWithLog(matWSrc);
            }
            frameIndex++;

            //imshow("Test", matWSrc.matImg);

            auto t1 = high_resolution_clock::now();
            faceDetect.logs[i].totalTime = duration_cast<milliseconds>(t1 - t0).count();


            matWSrc.~MatAdapter();


        }
        auto end = high_resolution_clock::now();
        totalTime = duration_cast<milliseconds>(end - start).count();
        report(faceDetect);
        // Register total time for process and display image.
//        waitKey(0);
//        destroyAllWindows();
    }


}

int main(int argc, char **argv) {
    dzapp::configureParams(argc, argv);
    dzapp::processImages();
    return 0;
}


