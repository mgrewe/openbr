#include <openbr/openbr_plugin.h>
#include <iostream>
#include <vector>
#include <string>
using namespace br;

int main(int argc, char *argv[])
{
	br::Context::initialize(argc, argv);

	std::vector<std::string> classifiers;
	std::string preprocessor="Cascade(FrontalFace)+FilterMetadata(Confidence,ge,3000)+DLandmarker()+ProcrustesAligner+PointsToMatrix(pos=68,length=68)";

	std::string videoDevice="1.webcam";

	classifiers.push_back("emotion_classifier_1");
	classifiers.push_back("emotion_classifier_2");
	classifiers.push_back("emotion_classifier_3");
	classifiers.push_back("emotion_classifier_4");
	classifiers.push_back("emotion_classifier_5");
	classifiers.push_back("emotion_classifier_6");
	classifiers.push_back("emotion_classifier_7");

	std::vector<QSharedPointer<br::Transform> > transforms;

	for (std::vector<std::string>::const_iterator classifier = classifiers.begin(); classifier != classifiers.end(); ++classifier){
		transforms.push_back(br::Transform::fromAlgorithm(QString::fromStdString(*classifier)));
	}

	QSharedPointer<br::Transform> preprocessing = br::Transform::fromAlgorithm(QString::fromStdString(preprocessor));
	//br::Template input(br::File(QString::fromStdString(videoDevice)));
	File file(QString::fromStdString(videoDevice));
//    br::Gallery *temp = br::Gallery::make(file);
//    qint64 total = temp->totalSize();
//    delete temp;

	br::TemplateList data, output;
    data.append(file);

	QSharedPointer<br::Transform> show = br::Transform::fromAlgorithm("Show(false)");

//    QScopedPointer<Transform> pipeline(show);
//    QScopedPointer<Transform> stream(wrapTransform(pipeline.data(), "Stream(readMode=StreamGallery, endPoint="+outputDesc+")"));

	//show->projectUpdate(data,output);

	show->projectUpdate(data,output);
	br::Enroll(data);

	while (0){
//	    AlgorithmManager::getAlgorithm(gallery.)->enroll(input, gallery);

		std::cout << "Enroling" << std::endl;
		//show->projectUpdate(data,output);
		std::cout << "projecting" << std::endl;
//		br::Enroll(data);
//		AlgorithmManager::getAlgorithm(gallery.)->enroll(input, gallery);
//		data >> *show;
	}


	br::Context::finalize();
	std::cout << "END" << std::endl;

	return 0;
}
