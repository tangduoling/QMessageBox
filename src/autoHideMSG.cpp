class AutoHideDLG :public QMessageBox
{
public:
	AutoHideDLG();
	~AutoHideDLG();
	void showMSG(const QString&,int);


public slots:
void ontimeout();


private:
	QTimer* timeout_;
	int ntime_;
	QString sMsg_;

};

AutoHideDLG::AutoHideDLG()
{
	timeout_ = new QTimer(this);
	connect(timeout_, &QTimer::timeout,
		this, &AutoHideDLG::ontimeout);
	ntime_ = 3;
	sMsg_ = QStringLiteral("");
}


AutoHideDLG::~AutoHideDLG()
{
	if (timeout_->isActive())
	{
		timeout_->stop();
	}
				 
	if (nullptr != timeout_)
	{
		delete timeout_;
		timeout_ = nullptr;
	}
}

void AutoHideDLG::ontimeout()
{
	ntime_--;
	this->setText(sMsg_ + QStringLiteral("(") + QString::number(ntime_) + QStringLiteral("s 后消失)"));
	if (ntime_ == 0)
	{
		this->close();
	}
}
/*
*  sMsg    弹框的内容
*  seconds 多少秒后消失
*/
void AutoHideDLG::showMSG(const QString& sMsg,int seconds)
{
	if (0 >= seconds)
	{
		return;
	}

	sMsg_ = sMsg;
	this->setWindowTitle(CINFO);
	ntime_ = seconds;
	this->setText(sMsg_ + QStringLiteral("(") + QString::number(ntime_) + QStringLiteral("s 后消失)"));
	timeout_->start(1000);
	exec();
}