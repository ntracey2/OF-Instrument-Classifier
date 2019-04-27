/*
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

using namespace arma;
using namespace mlpack;
using namespace mlpack::naive_bayes;

int Classify() {
	cout << "[SAMPLE:BEGIN]";

	// (1) Load the dataset
	cout << "\nLoading dataset...";

	mat dataset;

	// CSV is loaded transposed (columns are samples, rows are dimensions)
	bool loaded = mlpack::data::Load("data.csv", dataset);
	if (!loaded)
		return -1;

	Row<size_t> labels;

	// Extract the labels from the last dimension of the training set
	labels = conv_to<Row<size_t>>::from(dataset.row(dataset.n_rows - 1));

	// Remove the labels from the training set
	dataset.shed_row(dataset.n_rows - 1);

	// (2) Training
	cout << "\nTraining...";

	NaiveBayesClassifier<mat> nbc;

	nbc = NaiveBayesClassifier<mat>(4, 2);

	Row<size_t> predictions;

	nbc.Classify(dataset, predictions);

	const size_t correct = arma::accu(predictions == labels);

	cout << "\nTraining Accuracy: " << (double(correct) / double(labels.n_elem));

	return 0;
}*/