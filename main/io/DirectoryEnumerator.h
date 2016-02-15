/**
 * Created by Hal@shurabaP on 2015/06/11.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_FILEENUMERATOR_H
#define HARUNEKO_FILEENUMERATOR_H

#include <functional>
#include <QDir>
#include <QFileInfo>
#include <QList>

namespace haruneko {
namespace util {
    /**
     * DirectoryEnumerator enumerates directories.
     * This type is supposed to use in test.
     */
    typedef std::function<QList<QDir>(const QDir &)> DirectoryEnumerator;
    extern const DirectoryEnumerator FileDirectoryEnumerator;
}
}


#endif //HARUNEKO_FILEENUMERATOR_H
