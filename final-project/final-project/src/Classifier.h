#pragma once

#include "mlpack/core.hpp"
#include "mlpack/methods/random_forest/random_forest.hpp"
#include "mlpack/methods/decision_tree/random_dimension_select.hpp"
#include "mlpack/core/cv/k_fold_cv.hpp"
#include "mlpack/core/cv/metrics/accuracy.hpp"
#include "mlpack/core/cv/metrics/precision.hpp"
#include "mlpack/core/cv/metrics/recall.hpp"
#include "mlpack/core/cv/metrics/F1.hpp"
#include "mlpack/methods/naive_bayes/naive_bayes_classifier.hpp"
#include "mlpack/methods/naive_bayes/naive_bayes_classifier_impl.hpp"
#include "mlpack/methods/logistic_regression/logistic_regression.hpp"

using namespace arma;
using namespace mlpack;
using namespace mlpack::naive_bayes;
using namespace mlpack::tree;

class Classifier {
private:
	NaiveBayesClassifier<mat> nbc;
	RandomForest<GiniGain, RandomDimensionSelect> rf;
	Row<size_t> labels;
	Row<size_t> predictions;
	mat dataset;

	Row<size_t> testlabels;
	Row<size_t> testpredictions;
	mat testset;

	int numClasses = 0;
	int numTrees = 10;
	int minimumLeafSize = 3;

public:
	void LoadData(std::string file);
	void LoadTestData(std::string file);

	void TrainNBC();
	void TrainRF();

	void ClassifyNBC();
	void ClassifyRF();


	void SaveNBCModel();
	void SaveRFModel();
	void LoadNBCModel(std::string file);
	void LoadRFModel(std::string file);

	std::vector<std::vector<float>> GetConfusionMatrix();
};