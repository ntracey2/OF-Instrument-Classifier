#include "Classifier.h"

void Classifier::LoadData(std::string file)
{
	bool loaded = mlpack::data::Load(file, dataset);
	if (!loaded) {
		std::cout << "Error loading training dataset" << std::endl;
	}
	dataset.shed_row(dataset.n_rows - 1);
	labels = conv_to<Row<size_t>>::from(dataset.row(dataset.n_rows - 1));
	dataset.shed_row(dataset.n_rows - 1);
}

void Classifier::LoadTestData(std::string file)
{
	bool loaded = mlpack::data::Load("testdata1.csv", testset);
	if (!loaded) {
		std::cout << "Error loading training dataset" << std::endl;
	}
	testset.shed_row(dataset.n_rows - 1);
	testlabels = conv_to<Row<size_t>>::from(testset.row(testset.n_rows - 1));
	testset.shed_row(testset.n_rows - 1);
}

void Classifier::TrainNBC()
{
	nbc = NaiveBayesClassifier<mat>(dataset, labels, numClasses, false);
}

void Classifier::TrainRF()
{
	rf = RandomForest<GiniGain, RandomDimensionSelect>(dataset, labels, numClasses, numTrees, minimumLeafSize);
}

void Classifier::ClassifyNBC()
{
	nbc.Classify(testset, testpredictions);
}

void Classifier::ClassifyRF()
{
	rf.Classify(testset, testpredictions);
}

void Classifier::SaveNBCModel()
{
	mlpack::data::Save("nbcmodel.xml", "model", nbc, false);
}
void Classifier::SaveRFModel()
{
	mlpack::data::Save("rfmodel.xml", "model", rf, false);
}

void Classifier::LoadNBCModel(std::string file)
{
	mlpack::data::Load(file, "model", nbc);
}
void Classifier::LoadRFModel(std::string file)
{
	mlpack::data::Load(file, "model", rf);
}

std::vector<std::vector<float>> Classifier::GetConfusionMatrix()
{
	std::vector<std::vector<float>> confusion;
	for (int i = 0; i < numClasses; i++) {
		for (int j = 0; j < numClasses; j++) {
			int sum1 = 0;
			int sum2 = 0;
			for (int k = 0; k < testpredictions.size(); k++) {
				if (testpredictions.at(k) == j && labels.at(k) == i) {
					sum1++;
				}
				if (labels.at(k) == i) {
					sum2++;
				}
			}
			confusion[i][j] = (double) sum1 / (double) sum2;
		}
	}
	return confusion;
}

void Classifier::setNumClasses(int n) {
	numClasses = n;
}