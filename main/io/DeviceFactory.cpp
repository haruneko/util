/**
 * Created by Hal@shurabaP on 2015/04/28.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#include <QFile>
#include "DeviceFactory.h"

using namespace haruneko::util;

const DeviceFactory haruneko::util::FileDeviceFactory =
        [] (const QFileInfo &info) -> QSharedPointer<QIODevice> {
            return QSharedPointer<QIODevice>(new QFile(info.filePath()));
        };
