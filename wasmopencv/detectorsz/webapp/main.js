"use strict";

const width = document.getElementById('width').textContent;
const height = document.getElementById('height').textContent;
const workloadName = "FACE_DETECT";
let totalFrames = 0;
let totalFramesProcessed = 0;
let datasetName = null;
let totalTime = null;
let countFileUploaded;
let faceDetect;

const processFiles = function (event) {
  let imageList = document.getElementById("imageList");
  imageList.innerHTML = "";

  countFileUploaded = event.target.files.length;

  let fileName = event.target.files[0].name;
  fileName = fileName.substring(0, fileName.lastIndexOf('_'));
  datasetName = fileName.substring(0, fileName.lastIndexOf('_'));

  for (let i = 0; i < event.target.files.length; i++) {
    let reader = new FileReader();
    reader.onload = function (readerEvent) {
      let listItem = document.createElement("li");
      listItem.innerHTML = "<img src='" + readerEvent.target.result + "' width='" + width + "'+ height='" + height + "'/>" +
        "<canvas id='" + i + "' width='" + width + "'+ height='" + height + "' />";
      imageList.append(listItem);
    }
    reader.onloadend = function (event) {
      countFileUploaded--;
      if (countFileUploaded === 0) {
        processImages();
      }
    }
    reader.readAsDataURL(event.target.files[i]);
  }
}

const processImages = function () {
  faceDetect = new Module.FaceDetect("DATASET1");
  let allImgElements = document.getElementsByTagName("img");
  totalFramesProcessed = 0;
  totalFrames = allImgElements.length;
  totalTime = performance.now();
  let control = totalFrames - 1;
  for (let i = 0; i < allImgElements.length; i++) {
    //console.log(i);
    let t0 = performance.now();

    let src = Module.readImage(allImgElements[i]);
    faceDetect.faceDetectWithLog(src);
    //Module.showImage("" + i, src);
    let t1 = performance.now();

    src.delete();
    faceDetect.updateTotalTime(i, t1 - t0);
    totalFramesProcessed++;
  }
  totalTime = performance.now() - totalTime;
  saveLogs();
  // //if (faceDetect != null && !faceDetect.isDeleted()) {
  //   faceDetect.delete();
  // }
}

const getSystemName = function () {
  let name = "Web";
  let osName = "Unknown OS";
  if (navigator.appVersion.indexOf("Win") != -1) osName = "Windows";
  if (navigator.appVersion.indexOf("Mac") != -1) osName = "MacOS";
  if (navigator.appVersion.indexOf("X11") != -1) osName = "UNIX";
  if (navigator.appVersion.indexOf("Linux") != -1) osName = "Linux";

  if (navigator.userAgent.indexOf('Firefox') > 0) {
    name = navigator.userAgent.substring(
      navigator.userAgent.indexOf("Firefox"),
      navigator.userAgent.indexOf("Firefox") + 10).replace("/", "_");
  } else if (navigator.userAgent.indexOf('Chrome') > 0) {
    name = navigator.userAgent.substring(
      navigator.userAgent.indexOf("Chrome"),
      navigator.userAgent.indexOf("Chrome") + 9)
      .replace("/", "_");
  }
  return name + "_" + osName;
}

const saveLogs = () => {
  let resLabel = document.getElementById('resLabel').textContent;
  let system = getSystemName();
  let head = ",system,resolution_label";
  let columns = "," + system + "," + resLabel;
  let reportName = "LOG_" + workloadName + "_" + datasetName + "_" +
    resLabel + "_" + system;
  let logData = new Blob(
    [faceDetect.logsToStringAndAddCommon(head, columns)],
    {type: 'application/csv'});
  let elemA = document.createElement('a');
  elemA.style.display = 'none';
  elemA.download = reportName + ".csv";
  elemA.href = URL.createObjectURL(logData)
  document.body.appendChild(elemA);
  elemA.click();
  document.body.removeChild(elemA);
  let metaLog = "workload,dataset,resolution,system,total_frames,"
    + "total_frames_processeds,test_total_time_ms,log_file\n";
  metaLog = metaLog + workloadName + "," + datasetName
    + "," + resLabel + "," + system + ","+totalFrames+"," + totalFramesProcessed
    + "," + totalTime + "," + reportName + ".csv";
  let metaLogData = new Blob([metaLog], {type: 'application/csv'});
  let elemB = document.createElement('a');
  elemB.style.display = 'none';
  elemB.download = "META_" + reportName + ".csv";
  elemB.href = URL.createObjectURL(metaLogData)
  document.body.appendChild(elemB);
  elemB.click();
}

const init = () => {
  console.log("WASM - João Lourenço Souza Jr");

  let inputFile = document.getElementById('inputFile')
  inputFile.addEventListener('change', processFiles, false);
};

var Module = {
  preRun: [],
  postRun: [init],
  print: function (text) {
    if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
    console.log(text);
  },
  printErr: function (text) {
    if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
    console.error(text);
  },
};
