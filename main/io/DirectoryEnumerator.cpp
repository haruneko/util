/**
 * Created by Hal@shurabaP on 2015/06/11.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#include <QFileInfo>
#include "DirectoryEnumerator.h"

const haruneko::util::DirectoryEnumerator haruneko::util::FileDirectoryEnumerator =
        [](const QDir &dir) -> QList<QDir> {
            QFileInfoList dirs = dir.entryInfoList(QDir::AllDirs | QDir::NoDotDot);
            QList<QDir> result;
            for(const QFileInfo &fileInfo : dirs) {
                result.append(QDir(fileInfo.filePath()));
            }
            return result;
        };
