#include "widescrollbar.h"

WideScrollBar::WideScrollBar()
{
    setStyleSheet("QScrollBar:vertical {min-width: 32px;}");
}
