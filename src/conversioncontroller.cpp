#include "conversioncontroller.h"

ConversionController::ConversionController(QObject *parent):
    QObject(parent)
{

}

ConversionController::~ConversionController()
{
    /* Kill current process if there
     * are files being converted
     */
    if (filesConverted > 0) {
        ffmpegProcess->kill();
    }
}
