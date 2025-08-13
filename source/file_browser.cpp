#include <SD.h>
#include "file_browser.h"
#include "tft_ui.h"
#include "userconfig.h"

String currentPath = "/";

void listTapeFiles(String path) {
  currentPath = path;
  File dir = SD.open(path);
  fileCount = 0;

  if (path != "/") {
    fileList[fileCount++] = "...";
  }

  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;
    String name = entry.name();
    name.toLowerCase();

    if (entry.isDirectory()) {
      if (fileCount < MAX_FILES) {
        fileList[fileCount++] = String(">") + name;
      }
    } else if (name != "logo.bmp" && (
        name.endsWith(".tap") || name.endsWith(".tzx") ||
        name.endsWith(".cdt") || name.endsWith(".cas"))) {
      if (fileCount < MAX_FILES) {
        fileList[fileCount++] = name;
      }
    }
    entry.close();
  }

  drawFileList();
}

String loadFileFromList() {
  String selected = fileList[selectedFile];
  if (selected == "...") {
    int slashIndex = currentPath.lastIndexOf('/');
    currentPath = (slashIndex <= 0) ? "/" : currentPath.substring(0, slashIndex);
    listTapeFiles(currentPath);
    return "";
  } else if (selected.startsWith(">")) {
    String folderName = selected.substring(1);
    String newPath = currentPath + "/" + folderName;
    listTapeFiles(newPath);
    return "";
  } else {
    return currentPath + "/" + selected;
  }
}
