
import os

dataset_dir = "./dataset"
dataset_img_dir = "./dataset/images"

resolutions = {
    "SMALL":"480x320",  #153600 px
    "MEDIUM":"768x480", #368640 px
    "LARGE":"1280x720" #921600 px
}


if not os.path.exists(dataset_dir):
    os.makedirs(dataset_dir)

if not os.path.exists(dataset_img_dir):
    os.makedirs(dataset_img_dir)

def download_video(params, name, youtube_link):
    if not os.path.exists(f"{dataset_dir}/{name}.mp4"):
        cmd =  f"youtube-dl -f '{params}' -o {dataset_dir}/{name}.mp4 {youtube_link}"
        print(cmd)
        os.system(cmd)

def extract_images(video, res):
    video_dir_path = f"{dataset_img_dir}/{video}_{res}"
    if not os.path.exists(video_dir_path):
        os.makedirs(video_dir_path)
        cmd =  f"ffmpeg -i {dataset_dir}/{video}.mp4 -vf fps=1 -s {resolutions[res]} {video_dir_path}/{video}_{res}_%06d.png"
        print(cmd)
        os.system(cmd)


download_video("(mp4)[height=1080]/[fps=24]", "DATASET1","https://www.youtube.com/watch?v=EWUdGRAwUpY")
download_video("(mp4)[height=1080]/[fps=30]", "DATASET2","https://www.youtube.com/watch?v=vQtLX6pW5eA")
download_video("(mp4)[height=1080]/[fps=50]", "DATASET3","https://www.youtube.com/watch?v=RuL5jVqc4Tg")


extract_images("DATASET1", "SMALL")
extract_images("DATASET1", "MEDIUM")
extract_images("DATASET1", "LARGE")

extract_images("DATASET2", "SMALL")
extract_images("DATASET2", "MEDIUM")
extract_images("DATASET2", "LARGE")

extract_images("DATASET3", "SMALL")
extract_images("DATASET3", "MEDIUM")
extract_images("DATASET3", "LARGE")

with open("dataset.csv",'w',encoding = 'utf-8') as f:
    f.write("id,extension,resolution,fps,youtube_link\n")
    f.write("DATASET1,mp4,1920x1080,24,https://www.youtube.com/watch?v=EWUdGRAwUpY\n")
    f.write("DATASET2,mp4,1920x1080,30,https://www.youtube.com/watch?v=vQtLX6pW5eA\n")
    f.write("DATASET3,mp4,1920x1080,50,https://www.youtube.com/watch?v=RuL5jVqc4Tg\n")