#include "launcher.h"

const QString Launcher::sViewerFile = "viewer.exe";

const QString Launcher::sTrajectoriesPath = "/res/attractors_data/trajectories";
const QString Launcher::sSectionsPath = "/res/attractors_data/section_shapes";

const QFlags<Qt::AlignmentFlag> Launcher::sCenterAlignment = Qt::AlignVCenter |
                                                             Qt::AlignHCenter;

Launcher::Launcher(QWidget* parent)
    : QMainWindow(parent)
    , mMainWidget(this)
    , mMainLayout(&mMainWidget)
{
    configureWindow();
}



Launcher::~Launcher()
{

}

void Launcher::configureWindow()
{
    setCentralWidget(&mMainWidget);
    mMainLayout.setAlignment(sCenterAlignment);

    mMainLayout.addLayout(&mAttractorsLayout);
    mMainLayout.setAlignment(&mAttractorsLayout, sCenterAlignment);

    /// First attractor.
    mAttractorsLayout.addLayout(&mFirstAttractorLayout);
    mAttractorsLayout.setAlignment(&mFirstAttractorLayout, sCenterAlignment);

    mFirstAttractorLayout.addWidget(&mFirstAttractorLabel);
    mFirstAttractorLayout.setAlignment(&mFirstAttractorLabel, sCenterAlignment);
    mFirstAttractorLabel.setText("First attractor:");

    mFirstAttractorLayout.addLayout(&mFirstAttractorConfigLayout);
    mFirstAttractorConfigLayout.setAlignment(&mFirstAttractorConfigLayout,
                                             sCenterAlignment);

    mFirstAttractorConfigLayout.addWidget(&mFirstAttractorTrajectoryComboBox);
    mFirstAttractorConfigLayout.setAlignment(&mFirstAttractorTrajectoryComboBox,
                                             sCenterAlignment);
    generateComboBox(&mFirstAttractorTrajectoryComboBox, sTrajectoriesPath);

    mFirstAttractorConfigLayout.addWidget(&mFirstAttractorSectionComboBox);
    mFirstAttractorConfigLayout.setAlignment(&mFirstAttractorSectionComboBox,
                                             sCenterAlignment);
    generateComboBox(&mFirstAttractorSectionComboBox, sSectionsPath);

    /// Second attractor.
    mAttractorsLayout.addLayout(&mSecondAttractorLayout);
    mAttractorsLayout.setAlignment(&mSecondAttractorLayout, sCenterAlignment);

    mSecondAttractorLayout.addWidget(&mSecondAttractorLabel);
    mSecondAttractorLayout.setAlignment(&mSecondAttractorLabel, sCenterAlignment);
    mSecondAttractorLabel.setText("Second attractor:");

    mSecondAttractorLayout.addLayout(&mSecondAttractorConfigLayout);
    mSecondAttractorConfigLayout.setAlignment(&mSecondAttractorConfigLayout,
                                              sCenterAlignment);

    mSecondAttractorConfigLayout.addWidget(&mSecondAttractorTrajectoryComboBox);
    mSecondAttractorConfigLayout.setAlignment(&mSecondAttractorTrajectoryComboBox,
                                              sCenterAlignment);
    generateComboBox(&mSecondAttractorTrajectoryComboBox, sTrajectoriesPath);

    mSecondAttractorConfigLayout.addWidget(&mSecondAttractorSectionComboBox);
    mSecondAttractorConfigLayout.setAlignment(&mSecondAttractorSectionComboBox,
                                              sCenterAlignment);
    generateComboBox(&mSecondAttractorSectionComboBox, sSectionsPath);

    mMainLayout.addLayout(&mControlsLayout);
    mMainLayout.setAlignment(&mControlsLayout, sCenterAlignment);

    mControlsLayout.addWidget(&mRunButton);
    mControlsLayout.setAlignment(&mRunButton, sCenterAlignment);
    mRunButton.setText("Run");
    connect(&mRunButton, &QPushButton::clicked, this, &Launcher::runViewer);
}

void Launcher::generateComboBox(QComboBox* comboBox, QString res)
{
    comboBox->clear();

    const auto dir = QDir(QDir::current().path() + res);
    const auto entries = dir.entryList();
    for (const auto& entry : entries)
    {
        if (entry.compare(".") && entry.compare(".."))
        {
            comboBox->addItem(entry);
        }
    }
}

void Launcher::runViewer()
{
    QFile viewerFile(sViewerFile);
    if (!viewerFile.exists())
    {
        throw std::runtime_error("Unable to locate binary to run.");
    }

    QStringList args;
    args << mFirstAttractorTrajectoryComboBox.currentText()  <<
            mFirstAttractorSectionComboBox.currentText()     <<
            mSecondAttractorTrajectoryComboBox.currentText() <<
            mSecondAttractorSectionComboBox.currentText();

    mViewerProcess = std::make_unique<QProcess>(this);
    mViewerProcess->start(sViewerFile, args);
}
